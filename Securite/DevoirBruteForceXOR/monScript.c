#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct 
{
    char buffer[1024];
    char cle;
} Arguments;

pthread_mutex_t print_mutex;  // Mutex pour éviter des affichages concurrentiels

// Convertir une chaîne hexadécimale en tableau de bytes
void hexTobytes(const char *hex, unsigned char *bytes, size_t length) {
    for(size_t i = 0; i < length; i++) {
        sscanf(&hex[i * 2], "%2hhx", &bytes[i]);
    }
}

// Fonction de décryptage avec une clé donnée
void decrypt(unsigned char *encrypted, size_t length, unsigned char key) {
    for(size_t i = 0; i < length; i++) {
        encrypted[i] ^= key;
    }
}

// Vérifie si le message commence par "cst"
int startCST(const unsigned char *message) {
    return message[0] == 'c' && message[1] == 's' && message[2] == 't';
}

// Lecture du fichier et conversion en chaîne hexadécimale
int read_file(const char *filename, char **hex_data) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    *hex_data = malloc(file_size + 1);

    fread(*hex_data, 1, file_size, file);
    (*hex_data)[file_size] = '\0';
    fclose(file);
    return 1;
}

// Affichage du message déchiffré, caractère par caractère
void print(unsigned char *decrypted, size_t length) {
    for(size_t i = 0; i < length; i++) {
        if(decrypted[i] >= 32 && decrypted[i] <= 126) {
            printf("%c", decrypted[i]);
        } else {
            printf(".");
        }
    }
}

// Structure pour passer les arguments aux threads
typedef struct {
    unsigned char *encrypted;
    size_t message_length;
    unsigned char key_start;
    unsigned char key_end;
} ThreadArgs;

// Fonction exécutée par chaque thread pour tester une plage de clés
void *decrypt_range(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    unsigned char decrypted[args->message_length];
    unsigned char *encrypted = args->encrypted;
    size_t message_length = args->message_length;

    for(unsigned char key = args->key_start; key <= args->key_end; key++) {
        // Afficher la clé en cours de test
        pthread_mutex_lock(&print_mutex);
        printf("Thread teste la cle : 0x%02x\n", key);
        pthread_mutex_unlock(&print_mutex);

        memcpy(decrypted, encrypted, message_length);
        decrypt(decrypted, message_length, key);

        // Vérifier si le message commence par "cst"
        if (startCST(decrypted)) {
            pthread_mutex_lock(&print_mutex);
            printf("Cle trouver : 0x%02x\n", key);
            printf("Message dechiffrer: ");
            print(decrypted, message_length);
            pthread_mutex_unlock(&print_mutex);
            pthread_exit(NULL);  // Quitter dès qu'une clé est trouvée
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier_hex>\n", argv[0]);
        return 1;
    }

    const char *fichier = argv[1];
    char *hex_data = NULL;

    if (!read_file(fichier, &hex_data)) {
        return 1;
    }

    size_t hex_length = strlen(hex_data);
    size_t message_length = hex_length / 2;
    unsigned char encrypted[message_length];

    // Convertir les données hexadécimales en bytes
    hexTobytes(hex_data, encrypted, message_length);
    free(hex_data);

    // Initialisation du mutex pour les affichages
    pthread_mutex_init(&print_mutex, NULL);

    pthread_t threads[4];  // Utilisation de 4 threads pour diviser le travail
    ThreadArgs args[4];

    // Diviser la plage de clés entre les threads
    unsigned char key_range = 0xFF / 4;  // Diviser la plage de 0x00 à 0xFF en 4 parts égales
    for (int i = 0; i < 4; i++) {
        args[i].encrypted = encrypted;
        args[i].message_length = message_length;
        args[i].key_start = i * key_range;
        args[i].key_end = (i == 3) ? 0xFF : (i + 1) * key_range - 1;

        if (pthread_create(&threads[i], NULL, decrypt_range, &args[i]) != 0) {
            perror("Erreur de création du thread");
            return 1;
        }
    }

    // Attendre que tous les threads terminent leur travail
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruction du mutex
    pthread_mutex_destroy(&print_mutex);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void help()
{
    printf("hash_calculate parameter:\n");
    printf("-t  followed by a text string.\n");
    printf("-h  followed by a hex formated string.\n");
    printf("For example, hash_calculate -t abc -h 9a0d\n");
    printf("  which means concatenation of 9a0d to abc, then calculate hash.\n");
}

int convert_hex_to_str(char *str_in, char **str_out)
{
    int len;
    int i;
    int j;
    unsigned int val;
    char tmp[3] = {0};

    len = strlen(str_in);
    if (len == 0) {
        return 0;
    }
    if (len % 2 != 0) {
        tmp[0] = 0;
        tmp[1] = str_in[0];
    } else {
        tmp[0] = str_in[0];
        tmp[1] = str_in[1];
    }
    *str_out = malloc((len + 1) / 2);
    if (*str_out == NULL) {
        return 0;
    }

    for (j = 0, i = 2 - len % 2; i < len; j++) {
        sscanf(tmp, "%x", &val);
        (*str_out)[j] = val;
        tmp[0] = str_in[i++];
        tmp[1] = str_in[i++];
    }
    sscanf(tmp, "%x", &val);
    (*str_out)[j] = val;
    return (j + 1);
}

/* Output the hash string to screen */
void output_to_screen(char *flag, unsigned char *buf, int len)
{
    int i;

    printf("%s: ", flag);
    for (i = 0; i < len; i++) {
        printf("%.2hhx", buf[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int i;
    int ret;
    char *buf = NULL;
    unsigned char sha1_out[SHA_DIGEST_LENGTH];
    unsigned char sha256_out[SHA256_DIGEST_LENGTH];
    SHA_CTX ctx_1;
    SHA256_CTX ctx_256;

    if (argc <= 1) {
        help();
        return -1;
    }

    SHA1_Init(&ctx_1);
    SHA256_Init(&ctx_256);

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") != 0 && strcmp(argv[i], "-h") != 0) {
            help();
            return -1;
        }

	/* Accept string to calculate hash */
        if (strcmp(argv[i], "-t") == 0) {
            i++;
            SHA1_Update(&ctx_1, argv[i], strlen(argv[i]));
            SHA256_Update(&ctx_256, argv[i], strlen(argv[i]));
            continue;
        }
        i++;
        ret = convert_hex_to_str(argv[i], &buf);
        SHA1_Update(&ctx_1, buf, ret);
        SHA256_Update(&ctx_256, buf, ret);
        free(buf);
        continue;
    }

    SHA1_Final(sha1_out, &ctx_1);
    output_to_screen("sha1", sha1_out, sizeof(sha1_out));

    SHA256_Final(sha256_out, &ctx_256);
    output_to_screen("sha256", sha256_out, sizeof(sha256_out));

    return 0;
}

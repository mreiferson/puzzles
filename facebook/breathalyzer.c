#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF_SZ 1024 * 512
#define SM_BUF_SZ 1024

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void lowercase(char *string)
{
    char *tmp = string;
    
    while (*tmp != '\0') {
        *tmp = tolower(*tmp);
        tmp++;
    }
}

int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    int len_a = strlen(*ia);
    int len_b = strlen(*ib);
    
    return (len_a == len_b) ? 0 : ((len_a < len_b) ? -1 : 1);
} 

int calc_distance(const char *s, const char *t)
{
    int m,n,i,j,c;
    int d[SM_BUF_SZ];
    
    if (!strcmp(s, t)) {
        return 0;
    }
    
    m = strlen(s) + 1;
    n = strlen(t) + 1;
    
    for (i = 0; i < m; i++) {
        d[i] = i;
    }
    
    for (j = 0; j < n; j++) {
        d[j * m] = j;
    }
    
    for (j = 1; j < n; j++) {
        for (i = 1; i < m; i++) {
            if (s[i - 1] == t[j - 1]) {
                d[j * m + i] = d[(j - 1) * m + (i - 1)];
            } else {
                d[j * m + i] = min(min(d[(j - 1) * m + i] + 1, 
                                    d[j * m + (i - 1)] + 1), 
                                    d[(j - 1) * m + (i - 1)] + 1);
            }
        }
    }
    
    c = d[m * n - 1];
    
    return c;
}

int main(int argc, char **argv)
{
    char buf[BUF_SZ];
    char *filename;
    char *accepted_word_file = "breathalyzer.words";
    char *accepted_words[200000];
    char *word;
    int c, i, cur_min, word_len, accepted_word_len;
    int total, corrections;
    int len;
    FILE *fp;
    
    fp = fopen(accepted_word_file, "r");
    c = 0;
    while (fgets(buf, BUF_SZ, fp) != NULL) {
        len = strlen(buf);
        buf[len - 2] = '\0';
        lowercase(buf);
        accepted_words[c++] = strdup(buf);
    }
    fclose(fp);
    
    qsort(accepted_words, c, sizeof(char *), cstring_cmp);
    
    total = 0;
    filename = argv[1];
    fp = fopen(filename, "r");
    while (fgets(buf, BUF_SZ, fp) != NULL) {
        word = strtok(buf, " ");
        while (word != NULL) {
            word_len = strlen(word);
            
            if (word[word_len - 1] == '\n') {
                word[word_len - 1] = '\0';
            }
            
            cur_min = -1;
            for (i = 0; i < c; i++) {
                accepted_word_len = strlen(accepted_words[i]);
                
                if ((abs(word_len - accepted_word_len) > (cur_min + 1)) && (cur_min != -1)) {
                    break;
                }
                
                corrections = calc_distance(word, accepted_words[i]);
                
                if ((corrections < cur_min) || (cur_min == -1)) {
                    cur_min = corrections;
                }
                
                if (cur_min == 0) {
                    break;
                }
            }
            
            total += cur_min;
            
            //fprintf(stdout, "%s: %d\n", word, cur_min);
            
            word = strtok(NULL, " ");
        }
    }
    fclose(fp);
    
    for (i = 0; i < c; i++) {
        free(accepted_words[i]);
    }
    
    fprintf(stdout, "%d\n", total);
    
    return 0;
}

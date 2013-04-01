/* 
 * Knuth-Morris-Pratt string searching algorithm 
 * C Language Implementation
 * ref: chapter 32 in CLRS
 * author: wokaokeji
 */         
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERR_OUT stderr

#define PATTERN "aabcaa"
#define TEXT "abcaabcaabcaa"

struct kmp_str{
    u_char* data;   /* characters */
    int     len;    /* len of characters(exclude '\0') */
};
typedef struct kmp_str kmp_str_t;

#define kmp_string(str) {(u_char*)(str), sizeof(str) - 1}
#define disp_kmp_str(k_str)     \
    printf(#k_str":\tlen=%d\t\tdata=%s\n", (k_str)->len, (k_str)->data);

int* compute_prefix_function(kmp_str_t *pattern);
int kmp_matcher(kmp_str_t *text, kmp_str_t *pattern);

int main()
{
    printf("Start...\n");
    kmp_str_t text = kmp_string(TEXT);
    kmp_str_t pattern = kmp_string(PATTERN);
    disp_kmp_str(&text);
    disp_kmp_str(&pattern);
    
    printf("----Start to match-------\n");
    kmp_matcher(&text, &pattern);

    printf("End...\n");
    return 0;
}


int* compute_prefix_function(kmp_str_t *pattern)
{
    int m = pattern->len;
    int *pi = malloc(sizeof(int) * (m + 1));
    if (NULL == pi)
    {
        fprintf(ERR_OUT, "ERROR in %s()\n", __func__);
        return NULL;
    }
    pi[1] = 0;
   
    int k = 0;  /* number of characters matched  */
    int q;
    for (q = 1; q < m; ++q)
    {
        /* invariant: k = pi[q]*/
        while (k > 0 && pattern->data[q] != pattern->data[k] /*no.(k+1)*/)
        {
            k = pi[k];
        }
        /* k = max(H_q) or 0 */

        if (pattern->data[q] == pattern->data[k])
        {
            ++k;
            /* k = 1 + max(H_q) */
        }
        else
        {
            /* k = 0 */
        }

        pi[q + 1] = k;
    }

    return pi;
}

int kmp_matcher(kmp_str_t *text, kmp_str_t *pattern)
{
    int m = pattern->len;
    int n = text->len;
    int k = 0;  /* number of characters matched */

    int *pi = compute_prefix_function(pattern);

    int i;
    for (i = 0; i < n; ++i)
    {
        while (k > 0 && text->data[i] != pattern->data[k])
        {
            /* next character does not match */
            k = pi[k];
        }

        if(text->data[i] == pattern->data[k])
        {
            /* next character matches */
            ++k;
        }

        if (m == k)
        {
            printf("MATCHED: %.*s, shift = %d\n", 
                    m, text->data + i - m + 1, i - m + 1);
            /* look for the next match */
            k = pi[k];
        }
    }
    
    free(pi);
    pi = NULL;
    return 1;
}


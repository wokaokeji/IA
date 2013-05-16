#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define ERR_OUT stderr

struct kmp_str{
    u_char* data;
    int     len;
};

typedef struct kmp_str kmp_str_t;

#define kmp_string(str) {(u_char*)(str) - 1, sizeof(str) - 1}
#define disp_kmp_str(k_str)     \
    printf(#k_str":\ndata=%s, len=%d\n", (k_str)->data + 1, (k_str)->len);

#define PATTERN "asdf"
#define TEXT "ASDFADGasdfagargagasdfkjkijkj"


int compute_prefix_function(kmp_str_t *pattern, int *pi);
int kmp_matcher(kmp_str_t *text, kmp_str_t *pattern);

int main()
{
    printf("Start...\n");
    printf("测试%*s", 4, "123456789\n");
    //kmp_str_t text, pattern;
    kmp_str_t text = kmp_string(TEXT);
    kmp_str_t pattern = kmp_string(PATTERN);
    disp_kmp_str(&text);
    disp_kmp_str(&pattern);
    
    kmp_matcher(&text, &pattern);

    printf("End...\n");
    return 0;
}


int compute_prefix_function(kmp_str_t *pattern, int *pi)
{
    int m = pattern->len;
    pi[1] = 0;
    int k = 0;  /* comman len */
    int q;
    for (q = 2; q <= m; ++q)
    {
        /* invariant: k = pi[q-1]*/
        while (k > 0 && pattern->data[q] != pattern->data[k+1])
        {
            k = pi[k];
        }
        /* k = max(H_q-1) */

        if (pattern->data[q] == pattern->data[k+1])
        {
            ++k;
        }

        pi[q] = k;
    }

    return 1;
}

int kmp_matcher(kmp_str_t *text, kmp_str_t *pattern)
{
    int m = pattern->len;
    int n = text->len;
    int k = 0;  /* comman len */

    int *pi = malloc(sizeof(int) * (pattern->len + 1));
    if (NULL == pi)
        fprintf(ERR_OUT, "ERROR in %s()\n", __func__);
    compute_prefix_function(pattern, pi);
    int i;
    for (i = 1; i <= n; ++i)
    {
        while (k>0 && text->data[i] != pattern->data[k+1])
        {
            k = pi[k];
        }

        if(text->data[i] == pattern->data[k+1])
        {
            ++k;
        }

        if (m == k)
        {
            printf("MATCHED: %*s, shift = %d\n", 
                    4, text->data + i - m + 1, i - m);
            k = pi[k];
        }
    }
    
    free(pi);
    pi = NULL;
    return 1;
}


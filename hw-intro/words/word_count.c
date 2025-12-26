/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"

/* Basic utilities */

char *new_string(char *str) {
    char *new_str = (char *)malloc(strlen(str) + 1);
    if (new_str == NULL) {
        return NULL;
    }
    return strcpy(new_str, str);
}

int init_words(WordCount **wclist) {
    if (wclist == NULL) {
        return 1;
    }
    *wclist = NULL;
    return 0;
}

int init_word(WordCount **wclist) {
    /* Initialize word count.
       Returns 0 if no errors are encountered
       in the body of this function; 1 otherwise.
    */

    WordCount *current = (WordCount *)malloc(sizeof(WordCount));
    if (current == NULL) {
        return 1;
    }
    current->count = 0;
    current->word = NULL;
    current->next = NULL;

    *wclist = current;

    return 0;
}

ssize_t len_words(WordCount *wchead) {
    /* Return -1 if any errors are
       encountered in the body of
       this function.
    */
    WordCount *wc = wchead;
    size_t len = 0;
    while (wc != NULL) {
        wc = wc->next;
        len += 1;
    }
    return len;
}

WordCount *find_word(WordCount *wchead, char *word) {
    /* Return count for word, if it exists */
    WordCount *wc = NULL;

    while (wchead != NULL) {
        bool eq = strlen(word) == strlen(wchead->word);
        for (int i = 0; i < strlen(word) && eq; i++) {
            if (word[i] != wchead->word[i]) {
                eq = false;
            }
        }

        // fprintf(stdout, "#debug: f:find_word %s\n", wchead->word);

        if (eq) {
            wc = wchead;
            break;
        }

        wchead = wchead->next;
    }

    return wc;
}

int add_word(WordCount **wclist, char *word) {
    /* If word is present in word_counts list, increment the count.
       Otherwise insert with count 1.
       Returns 0 if no errors are encountered in the body of this function; 1
       otherwise.
    */
    WordCount *wc = find_word(*wclist, word);

    if (wc == NULL) {
        WordCount *current;
        if (init_word(&current) == 0) {
            current->word = word;
            current->count = 1;
            current->next = *wclist;
            *wclist = current;
        } else {
            return 1;
        }
    } else {
        wc->count += 1;
    }

    return 0;
}

void fprint_words(WordCount *wchead, FILE *ofile) {
    /* print word counts to a file */
    WordCount *wc;
    for (wc = wchead; wc; wc = wc->next) {
        fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
    }
}

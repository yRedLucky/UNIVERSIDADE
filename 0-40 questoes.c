#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define MAXLINE 1024

char buffer[MAXLINE];

// 1 - Defina um programa que lˆe (usando a fun¸c˜ao scanf uma sequˆencia de n´umeros inteiros terminada com o n´umero 0 e imprime no ecran o maior elemento da sequˆencia.


void one() {
    int largest = INT_MIN;
    puts("Maior de uma sequência\nInsere uma lista de números (um por linha) terminada em 0:");
    while(1) {
        int num;
        assert(scanf("%d",&num) == 1);
        if(num == 0) break;
        if(num > largest) largest = num;
    }
    printf("Maior: %d\n", largest);
}

// 2 - Defina um programa que lˆe (usando a fun¸c˜ao scanf uma sequˆencia de n´umeros inteiros terminada com o n´umero 0 e imprime no ecran a m´edia da sequˆencia.

void two() {
    double soma = 0;
    int n = 0;
    while(1) {
        int num;
        assert(scanf("%d",&num) == 1);
        if(num == 0) break;
        soma += num;
        n++;
    }
    double media = soma / n;
    printf("Média: %.5f\n", media);
}

// 3 -  Defina um programa que lˆe (usando a fun¸c˜ao scanf uma sequˆencia de n´umeros inteiros terminada com o n´umero 0 e imprime no ecran o segundo maior elemento.


void three() {
    int biggest = INT_MIN, second_biggest = INT_MIN, num;
    while(1) {
        assert(scanf("%d",&num) == 1);
        if(num == 0) break;
        if(num > biggest) {
            second_biggest = biggest;
            biggest = num;
        } else if (num > second_biggest) second_biggest = num;
    }
    printf("Segundo maior número: %d\n", second_biggest);
}

// 4 - Defina uma fun¸c˜ao int bitsUm (unsigned int n) que calcula o n´umero de bits iguais a 1 usados na representa¸c˜ao bin´aria de um dado n´umero n.

int bitsUm (unsigned int n){
    int r = 0;
    while(n) {
        r += (n % 2);
        n >>= 1; // Shifts the bits in `n` one bit to the right, i.e., n = n / 2
    }
    return r;
}

// 5 -  Defina uma fun¸c˜ao int trailingZ (unsigned int n) que calcula o n´umero de bits a 0 nofinal da representa¸c˜ao bin´aria de um n´umero (i.e., o expoente da maior potˆencia de 2 que ´edivisor desse n´umero)

int trailingZ (unsigned int n) {
    if(n % 2) return 0;
    else return 1 + trailingZ(n >> 1);
}

// 6 - Defina uma fun¸c˜ao int qDig (unsigned int n) que calcula o n´umero de d´ıgitos necess´arios para escrever o inteiro n em base decimal. Por exemplo, qDig (440) deve retornar 3.

int qDig (unsigned int n) {
    if(n / 10 < 1) return 1;
    else return 1 + qDig(n / 10);
}

// 7 - Apresente uma defini¸c˜ao da fun¸c˜ao pr´e-definida em C char *strcat (char s1[], char s2[]) que concatena a string s2 a s1 (retornando o endere¸co da primeira).

char* mystrcat(char s1[], char s2[]) {
    char* cat = s1;
    while(*s1) s1++;
    while((*s1 = *s2)) {s1++; s2++;}
    *s1 = '\0';
    return cat;
}

// 8 - Apresente uma defini¸c˜ao da fun¸c˜ao pr´e-definida em C char *strcpy (char *dest, char source[]) que copia a string source para dest retornando o valor desta ´ultima.

char* mystrcpy(char* dest, char source[]) {
    char* result = dest;
    while((*dest = *source)) { source++; dest++; }
    return result;
}

// 9 - Apresente uma defini¸c˜ao da fun¸c˜ao pr´e-definida em C int strcmp (char s1[], char s2[])que compara (lexicograficamente) duas strings. O resultado dever´a ser
// • 0 se as strings forem iguais
// • <0 se s1 < s2
// • >0 se s1 > s2


int mystrcmp(char s1[], char s2[]) {
    while(*s1 == *s2 && *s1) { s1++; s2++; }
    return *s1 - *s2;
}

// 10 - Apresente uma defini¸c˜ao da fun¸c˜ao pr´e-definida em C char *strstr (char s1[], char s2[]) que determina a posi¸c˜ao onde a string s2 ocorre em s1. A fun¸c˜ao dever´a retornar NULL caso s2 n˜ao ocorra em s1

char* mystrstr (char haystack[], char needle[]) {
    int isContained = 1;
    char* ans = haystack;
    char* needleStart = needle;
    while(*needle && *haystack) {
        if(*haystack != *needle) {
            isContained = 0;
            needle = needleStart;
        }
        if(*haystack == *needle) {
            if(!isContained) {
                isContained = 1;
                ans = haystack;
            }
            needle++;
        }
        haystack++;
    }
    if (isContained && !(*needle)) return ans;
    else return NULL;
}

// 11 - Defina uma fun¸c˜ao void strrev (char s[]) que inverte uma string.

void mystrrev(char s[]) {
    int len;
    for(len = 0; s[len]; len++);
    char rev[len];
    for(int i = 0; i < len; i++) rev[i] = s[len - i - 1];
    for(int i = 0; i < len; i++) s[i] = rev[i];
}

// 12 - Defina uma fun¸c˜ao void strnoV (char s[]) que retira todas as vogais de uma string

void tail(char* s) {
    for(; *s; s++)
        *s = *(s+1);
}

void strnoV (char s[]) {
    while(*s) {
        if(*s == 'A' || *s == 'E' || *s == 'I' || *s == 'O' || *s == 'U' || *s == 'a'
        || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u') tail(s);
        else s++;
    }
}

// 13 - Defina uma fun¸c˜ao void truncW (char t[], int n) que dado um texto t com v´arias palavras (as palavras est˜ao separadas em t por um ou mais espa¸cos) e um inteiro n, trunca todas as palavras de forma a terem no m´aximo n caracteres. Por exemplo, se a string txt contiver "liberdade, igualdade e fraternidade", a invoca¸c˜ao de truncW (txt, 4) deve fazer com que passe a estar l´a armazenada a string "libe igua e frat".

void truncW (char t[], int n) {
    int wordLen = 0;
    while(*t) {
        if(*t == ' ' || *t == '\n' || *t == '\t') {t++; wordLen = 0;}
        else {
            if(wordLen++ >= n) tail(t);
            else t++;
        }
    } 
}

// 14 - Defina uma fun¸c˜ao char charMaisfreq (char s[]) que determina qual o caracter mais frequente numa string. A fun¸c˜ao dever´a retornar 0 no caso de s ser a string vazia.

int freqC(char ch, char s[]) {
    int freq = 0;
    for(int i = 0; s[i]; i++) {
        if(s[i] == ch) freq++;
    }
    return freq;
}

char charMaisFreq(char s[]) {
    char maisFreq = 0;
    int freqMax = 0, freq;
    for(int i = 0; s[i]; i++) {
        if((freq = freqC(s[i],s)) > freqMax) {
            freqMax = freq;
            maisFreq = s[i];
        }
    }
    return maisFreq;
}

// 15 - Defina uma fun¸c˜ao int iguaisConsecutivos (char s[]) que, dada uma string s calcula o comprimento da maior sub-string com caracteres iguais. Por exemplo, iguaisConsecutivos ("aabcccaac") deve dar como resultado 3, correspondendo `a repeti¸c˜ao "ccc"

int iguaisConsecutivos (char s[]) {
    int consec = 1, max = 0;
    for(int i = 0; s[i]; i++) {
        if(s[i] == s[i + 1]) consec++;
        else {
            if(consec > max) max = consec;
            consec = 1;
        }
    }
    return max;
}

// 16 -  Defina uma fun¸c˜ao int difConsecutivos (char s[]) que, dada uma string s calcula o comprimento da maior sub-string com caracteres diferentes. Por exemplo, difConsecutivos ("aabcccaac") deve dar como resultado 3, correspondendo `a string "abc".

int not_in_prev(char str[], int k, int n) {
    int ans = 1;
    for(int i = k; i < n; i++) {
        if(str[i] == str[n]) {
            return 0;
        }
    }
    return ans;
}

int difConsecutivos(char s[]) {
    int ans = 0;
    for(size_t i = 0; s[i]; i++) {
        int consec = 0;
        for(size_t j = i; s[j]; j++) {
            if(not_in_prev(s,i,j)) consec++;
            else break;
        }
        if (consec > ans) ans = consec;
    }
    return ans;
}

// 17 - Defina uma fun¸c˜ao int maiorPrefixo (char s1 [], char s2 []) que calcula o comprimento do maior prefixo comum entre as duas strings

int maiorPrefixo (char s1 [], char s2 []) {
    int i;
    for(i = 0; s1[i] == s2[i] && s1[i]; i++);
    return i;
}

// 18 - Defina uma fun¸c˜ao int maiorSufixo (char s1 [], char s2 []) que calcula o comprimento do maior sufixo comum entre as duas strings.

int maiorSufixo (char s1 [], char s2 []) {
    int i, j, ans = -1;
    for(i = 0; s1[i]; i++);
    for(j = 0; s2[j]; j++);
    while(s1[i--] == s2[j--]) ans++;
    return ans;
}

// 19 - Defina a fun¸c˜ao int sufPref (char s1[], char s2[]) que calcula o tamanho do maior sufixo de s1 que ´e um prefixo de s2. Por exemplo sufPref("batota","totalidade") deve dar como resultado 4, uma vez que a string "tota" ´e um sufixo de "batota" e um prefixo de "totalidade".

int sufPref (char s1[], char s2[]) {
    int ans = 0, i, j = 0;
    for(i = 0; s1[i]; i++) {
        if(s1[i] == s2[j++]) ans++;
        else ans = j = 0;
    }
    return ans;
}

// 20 -  Defina uma fun¸c˜ao int contaPal (char s[]) que conta as palavras de uma string. Uma palavra ´e uma sequˆencia de caracteres (diferentes de espa¸co) terminada por um ou mais espa¸cos. Assim se a string p tiver o valor "a a bb a", o resultado de contaPal (p) deve ser 4.

int contaPal (char s[]) {
    int inWord = 0, total = 0;
    for(int i = 0; s[i]; i++) {
        if(s[i] == ' ' || s[i] == '\n') {
            if(inWord) total++;
            inWord = 0;
        }
        else inWord = 1;
    }
    if(inWord) total++;
    return total;
}

// 21 - Defina uma fun¸c˜ao int contaVogais (char s[]) que retorna o n´umero de vogais da strings. N˜ao se esque¸ca de considerar tanto mai´usculas como min´usculas.

int contaVogais (char s[]) {
    int total = 0;
    for(int i = 0; s[i]; i++) {
        switch(s[i]) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                total++;
        }
    }
    return total;
}

// 22 -  Defina uma fun¸c˜ao int contida (char a[], char b[]) que testa se todos os caracteres da primeira string tamb´em aparecem na segunda. Por exemplo, contida "braga" "bracara augusta" deve retornar verdadeiro enquanto que contida "braga" "bracarense" deve retornar falso.

int contida (char a[], char b[]) {
    int cont = 1;
    for(int i = 0; a[i]; i++) {
        int pertence = 0;
        for(int j = 0; b[j]; j++) {
            if(a[i] == b[j]) pertence = 1;
        }
        if(!pertence) {
            cont = 0;
            break;
        }
    }
    return cont;
}

// 23 - Defina uma fun¸c˜ao int palindorome (char s[]) que testa se uma palavra ´e pal´ındrome, i.e., lˆe-se de igual forma nos dois sentidos.

int palindrome (char s[]) {
    int len = 0;
    for(int i = 0; s[i]; i++) len++;
    for(int i = 0; s[i]; i++) if(s[i] != s[len - 1 - i]) return 0;
    return 1;
}

// 24 - Defina uma fun¸c˜ao int remRep (char x[]) que elimina de uma string todos os caracteres que se repetem sucessivamente deixando l´a apenas uma c´opia. A fun¸c˜ao dever´a retornar o comprimento da string resultante. Assim, por exemplo, ao invocarmos a fun¸c˜ao com uma vector contendo "aaabaaabbbaaa", o vector deve passar a conter a string "ababa" e a fun¸c˜ao dever´a retornar o valor 5

int remRep (char x[]) {
    if(!(*x)) return 0;
    int i = 1;
    char prev = x[0];
    while(x[i]) {
        if(x[i] == prev) tail(x + i);
        else prev = x[i++];
    }
    return i;
}

// 25 -  Defina uma fun¸c˜ao int limpaEspacos (char t[]) que elimina repeti¸c˜oes sucessivas de espa¸cos por um ´unico espa¸co. A fun¸c˜ao deve retornar o comprimento da string resultante. (

int limpaEspacos (char t[]) {
    int i = 0;
    int prevSpace = 0;
    while(t[i]) {
        if(t[i] == ' ') {
            if(prevSpace) {
                tail(t + i);
                continue;
            }
            else prevSpace = 1;
        }
        else prevSpace = 0;
        i++;
    }
    return i;
}

// 26 - Defina uma fun¸c˜ao void insere (int v[], int N, int x) que insere um elemento (x) num vector ordenado. Assuma que as N primeiras posi¸c˜oes do vector est˜ao ordenadas e que por isso, ap´os a inser¸c˜ao o vector ter´a as primeiras N+1 posi¸c˜oes ordenadas.

void insere (int v[], int N, int x) {
    for(int i = 0; i < N; i++) {
        if(v[i] > x) {
            for(int j = N; j > i; j--) {
                v[j] = v[j - 1];
            }
            v[i] = x;
            break;
        }
        if(i == N - 1) {
            v[N] = x;
        }
    }
}

// 27 - Defina uma fun¸c˜ao void merge (int r [], int a[], int b[], int na, int nb) que, dados vectores ordenados a (com na elementos) e b (com nb elementos), preenche o vector r (com na+nb elementos) com os elementos de a e b ordenados. 

void merge (int r [], int a[], int b[], int na, int nb) {
    int i = 0, j = 0, k = 0;
    while(k < na + nb) {
        if((a[i] < b[j] && i < na) || j >= nb)
            r[k++] = a[i++];
        else
            r[k++] = b[j++];
    }
}

void recursive_merge(int r[], int a[], int b[], int na, int nb) {
    if(na > 0) {
        if(nb > 0) {
            if(*a > *b) {
                *r = *b;
                recursive_merge(r+1, a, b+1, na, nb-1);
            }
            else {
                *r = *a;
                recursive_merge(r+1, a+1, b, na-1, nb);
            }
        }
        else {
            *r = *a;
            recursive_merge(r+1, a+1, b, na-1, nb);
        }
    }
    else if(nb > 0) {
        *r = *b;
        recursive_merge(r+1, a, b+1, na, nb-1);
    }
}

// 28 - Defina uma fun¸c˜ao int crescente (int a[], int i, int j) que testa se os elementos do vector a, entre as posi¸c˜oes i e j (inclusiv´e) est˜ao ordenados por ordem crescente. A fun¸c˜ao deve retornar 1 ou 0 consoante o vector esteja ou n˜ao ordenado.

int crescente (int a[], int i, int j) {
    int cresc = 1;
    for(int k = i; k < j; k++) {
        if(a[k + 1] < a[k]) cresc = 0;
    }
    return cresc;
}

// 29 - Defina uma fun¸c˜ao int retiraNeg (int v[], int N) que retira os n´umeros negativos de um vector com N inteiros. A fun¸c˜ao deve retornar o n´umero de elementos que n˜ao foram retirados.

int retiraNeg (int v[], int N) {
    int i = 0;
    while(i < N) {
        if(v[i] < 0) {
            for(int j = i; j < N - 1; j++) v[j] = v[j + 1];
            N--;
        }
        else i++;
    }
    return N;
}

// 30 - Defina uma fun¸c˜ao int menosFreq (int v[], int N) que recebe um vector v com N elementos ordenado por ordem crescente e retorna o menos frequente dos elementos do vector. Se houver mais do que um elemento nessas condi¸c˜oes deve retornar o que come¸ca por aparecer no ´ındice mais baixo.

int menosFreq (int v[], int N) {
    int freq = 1, minFreq = N, ans = v[0], i;
    for(i = 1; i < N; i++) {
        if(v[i] == v[i - 1]) freq++;
        if(v[i] != v[i - 1]) {
            if(freq < minFreq) {
                minFreq = freq;
                ans = v[i - 1];
            }
            freq = 1;
        }
    }
    if(freq < minFreq) {
        minFreq = freq;
        ans = v[i - 1];
    }
    return ans;
}

// 31 -  Defina uma fun¸c˜ao int maisFreq (int v[], int N) que recebe um vector v com N elementos ordenado por ordem crescente e retorna o mais frequente dos elementos do vector. Se houver mais do que um elemento nessas condi¸c˜oes deve retornar o que come¸ca por aparecer no ´ındice mais baixo.

int maisFreq (int v[], int N) {
    int freq = 1, maxFreq = 0, ans = v[0];
    for(int i = 1; i < N; i++) {
        if(v[i] == v[i - 1]) freq++;
        if(v[i] != v[i - 1]) {
            if(freq > maxFreq) {
                maxFreq = freq;
                ans = v[i - 1];
            }
            freq = 1;
        }
    }
    return ans;
}

// 32 - Defina uma fun¸c˜ao int maxCresc (int v[], int N) que calcula o comprimento da maior sequˆencia crescente de elementos consecutivos num vector v com N elementos. Por exemplo, se o vector contiver 10 elementos pela seguinte ordem: 1, 2, 3, 2, 1, 4, 10, 12, 5, 4, a fun¸c˜ao dever´a retornar 4, correspondendo ao tamanho da sequˆencia 1, 4, 10, 12

int maxCresc (int v[], int N) {
    int ans = 1, currAns = 1;
    for(int i = 1; i < N; i++) {
        if(v[i - 1] > v[i]) {
            ans = currAns > ans ? currAns : ans;
            currAns = 1;
        }
        else {
            currAns++;
        }
    }
    ans = currAns > ans ? currAns : ans;
    return ans;
}

// 33 - Defina uma fun¸c˜ao int elimRep (int v[], int n) que recebe um vector v com n inteiros elimina as repeti¸c˜oes. A fun¸c˜ao dever´a retornar o n´umero de elementos do vector resultante. Por exemplo, se o vector v contiver nas suas primeiras 10 posi¸c˜oes os n´umeros {1, 2, 3, 2, 1, 4, 2, 4, 5, 4} a invoca¸c˜ao elimRep (v,10) dever´a retornar 5 e colocar nas primeiras 5 posi¸c˜oes do vector os elementos {1,2,3,4,5}

int elimRep (int v[], int n) {
    int i = 1;
    while(i < n) {
        int belongs = 0;
        for(int j = 0; j < i; j++) {
            if(v[i] == v[j]) belongs = 1;
        }
        if(belongs) {
            for(int j = i; j < n; j++) {
                v[j] = v[j + 1];
            }
            n--;
        } else i++;
    }
    return n;
}

// 34 - Defina uma fun¸c˜ao int elimRepOrd (int v[], int n) que recebe um vector v com n inteiros ordenado por ordem crescente e elimina as repeti¸c˜oes. A fun¸c˜ao dever´a retornar o n´umero de elementos do vector resultante. 

int elimRepOrd (int v[], int n) {return elimRep(v,n);}

// 35 Defina uma fun¸c˜ao int comunsOrd (int a[], int na, int b[], int nb) que calcula quantos elementos os vectores a (com na elementos) e b (com nb elementos) tˆem em comum. Assuma que os vectores a e b est˜ao ordenados por ordem crescente. 

int comunsOrd (int a[], int na, int b[], int nb) {
    int i = 0, j = 0, ans = 0;
    while(i < na && j < nb) {
        if(a[i++] == b[j++]) {
            ans++;
            i++;
            j++;
        }
        else if(a[i] > b[j]) j++;
        else i++;
    }
    return ans;
}

// 36 -  Defina uma fun¸c˜ao int comuns (int a[], int na, int b[], int nb) que calcula quantos elementos os vectores a (com na elementos) e b (com nb elementos) tˆem em comum. Assuma que os vectores a e b n˜ao est˜ao ordenados e defina a fun¸c˜ao sem alterar os vectores.

int comuns (int a[], int na, int b[], int nb) {
    int ans = 0;
    for(int i = 0; i < na; i++) {
        int belongs = 0;
        for(int j = 0; j < nb; j++) if(a[i] == b[j]) belongs = 1;
        if(belongs) ans++;
    }
    return ans;
}

// 37 - Defina uma fun¸c˜ao int minInd (int v[], int n) que, dado um vector v com n inteiros, retorna o ´ındice do menor elemento do vector.

int minInd (int v[], int n) {
    int minIndex = 0;
    for(int i = 1; i < n; i++) 
        if(v[i] < v[minIndex]) 
            minIndex = i;
    return minIndex;
}

// 38 - Defina uma fun¸c˜ao void somasAc (int v[], int Ac [], int N) que preenche o vector
// Ac com as somas acumuladas do vector v. Por exemplo, na posi¸c˜ao Ac[3] deve ser calculado como v[0]+v[1]+v[2]+v[3].

void somasAc (int v[], int Ac [], int N) {
    for(int i = 0; i < N; i++) {
        Ac[i] = 0;
        for(int j = 0; j <= i; j++) {
            Ac[i] += v[j];
        }
    }
}

// 39 - Defina uma fun¸c˜ao int triSup (int N, float m [N][N]) que testa se uma matriz quadrada ´e triangular superior, i.e., que todos os elementos abaixo da diagonal s˜ao zeros.

int triSup (int N, float m [N][N]) {
    int x = 1;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            if(m[i][j]) x = 0;
        }
    }
    return x;
}

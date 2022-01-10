// Make10 サンプル
// 数字の入れ替え判断は出来ません
#include <stdio.h>

typedef int (*Op)(int, int);
int add(int a, int b) { return (a + b); }
int sub(int a, int b) { return (a - b); }
int mul(int a, int b) { return (a * b); }
int div(int a, int b) { return b ? (a / b) : 9999; }

Op o[] = { add, sub, mul, div };
char* op_str[] = { "＋", "－", "×", "÷" };
#if 1

int main() {
    int a, b, c, d; // オペランド
    int i, j, k;    // 演算子
    int n=0;

    // 標準入力(エラーチェックなし)
    char str[256];
    printf("4桁の数字を入力してください。\n");
    scanf_s("%s", str,256);
    printf("入力値は「%s」です。\n", str);

    a = str[0] - '0';
    b = str[1] - '0';
    c = str[2] - '0';
    d = str[3] - '0';

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
                // (a+b)+(c+d)
                if (o[j](o[i](a, b), o[k](c, d)) == 10) {
                   printf("(%d %s %d) %s (%d %s %d)\n", a, op_str[i], b, op_str[j], c, op_str[k], d);
                   n++;
                }
                
                // {(a+b)+c}+d
                if(o[k](o[j](o[i](a, b), c),d) == 10){
                   printf("{(%d %s %d) %s %d} %s %d\n", a, op_str[i], b, op_str[j], c, op_str[k], d);
                   n++;
                }

                // a+{b+(c+d)}
                if (o[i](a, o[j](b, o[k](c, d))) == 10) {
                    printf("%d %s {%d %s (%d %s %d)}\n", a, op_str[i], b, op_str[j], c, op_str[k], d);
                    n++;
                }

                // {a+(b+c)}+d
                if(o[k](o[i](a, o[j](b, c)), d) == 10){
                    printf("{%d %s (%d %s %d)} %s %d\n", a, op_str[i], b, op_str[j], c, op_str[k], d);
                    n++;
                }
                
                // a+{(b+c)+d}
                if (o[i](a, o[k](o[j](b, c), d)) == 10) {
                    printf("%d %s {(%d %s %d) %s %d}\n", a, op_str[i], b, op_str[j], c, op_str[k], d);
                    n++;
                }
            }
        }
    }
    if(n==0){
        printf("Not Found!\n");
    }
}

#else

int main()
{
    int a, b, c, d, i, j, k, n = 0;

    for (a = 0; a < 10; a++)
        for (b = 0; b < 10; b++)
            for (c = 0; c < 10; c++)
                for (d = 0; d < 10; d++)
                    for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                            for (k = 0; k < 4; k++)
                                n +=
                                (o[i](a, o[j](b, o[k](c, d))) != 10) +
                                (o[i](a, o[k](o[j](b, c), d)) != 10) +
                                (o[j](o[i](a, b), o[k](c, d)) != 10) +
                                (o[k](o[i](a, o[j](b, c)), d) != 10) +
                                (o[k](o[j](o[i](a, b), c), d) != 10);
    printf("%f %%\n", n * 100.0 / (10000 * 4 * 4 * 4 * 5));
    return 0;
}

#endif
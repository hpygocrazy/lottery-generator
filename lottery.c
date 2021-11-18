#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_VALUE 70
#define MAX_COLUMN_ARRAY MAX_VALUE - 4
#define MAX_ARRAY 37821919
#define FIVE_NUMBER_DIVISOR 120
#define FOUR_NUMBER_DIVISOR 24
#define THREE_NUMBER_DIVISOR 6
#define TWO_NUMBER_DIVISOR 2

struct Node
{
    uint32_t position;
    uint8_t number;
    struct Node *right;
    struct Node *left;
};

typedef struct Node BinaryTreeNode;

struct Lotto
{
    uint8_t first;
    uint8_t second;
    uint8_t third;
    uint8_t fourth;
    uint8_t fifth;
};

typedef struct Lotto LottoNumber;

struct PossibleCombinations
{
    uint32_t first[MAX_COLUMN_ARRAY];
    uint32_t second[MAX_COLUMN_ARRAY];
    uint32_t third[MAX_COLUMN_ARRAY];
    uint32_t fourth[MAX_COLUMN_ARRAY];
    uint32_t fifth[MAX_COLUMN_ARRAY];
};

typedef struct PossibleCombinations LottoCombos;

struct LottoBinarySearchTree
{
    BinaryTreeNode *first;
    BinaryTreeNode *second;
    BinaryTreeNode *third;
    BinaryTreeNode *fourth;
    BinaryTreeNode *fifth;
};

typedef struct LottoBinarySearchTree LottoBST;

long long calculateBitPosition(int a, int b, int c, int d, int e, int f)
{
    //This function works but takes a really long time.  Keeping for posterity

    long long bitPosition = 0;

    // mega number 1-25
    bitPosition += f - 1;

    // 5th number 5-MAX_VALUE
    bitPosition += (e - 5) * 25;

    // 4th number 4-69
    for (int i = d; i > 4; i--)
    {
        bitPosition += 1650 - ((i - 4) * 25);
    }

    // 3rd number 3-68
    for (int j = c; j > 3; j--)
    {
        bitPosition += 55275 - 1650;
        for (int k = j; k > 4; k--)
        {
            bitPosition -= 1650 - ((k - 4) * 25);
        }
    }

    // 2nd number 2-67
    for (int m = b; m > 2; m--)
    {
        bitPosition += 1252900 - 55275;
        for (int j = m; j > 3; j--)
        {
            bitPosition -= 55275 - 1650;
            for (int k = j; k > 4; k--)
            {
                bitPosition += 1650 - ((k - 4) * 25);
            }
        }
    }
    // 1st number 1-66
    for (int n = a; n > 1; n--)
    {
        bitPosition += 21612525 - 1252900;
        for (int m = n; m > 2; m--)
        {
            bitPosition -= 1252900 - 55275;
            for (int j = m; j > 3; j--)
            {
                bitPosition += 55275 - 1650;
                for (int k = j; k > 4; k--)
                {
                    bitPosition -= 1650 - ((k - 4) * 25);
                }
            }
        }
    }

    return bitPosition;
}

int calcOdd(int a, int count)
{
    // This function is no longer used

    return ((MAX_VALUE - (a + 1) - (count / 2)) * count);
}

int calcEven(int a, int count)
{
    // This function is no longer used

    int first;
    int second;
    float middle;

    first = MAX_VALUE - (a + 1) - ((count / 2) - 1);
    second = MAX_VALUE - (a + 1) - (count / 2);
    middle = first + second;
    middle /= 2;
    return (int)(middle * count);
}

int calcPosition(LottoCombos combos, LottoNumber lottoNumber)
{
    return combos.first[lottoNumber.first - 1] -
           combos.second[lottoNumber.second - 2] +
           combos.third[lottoNumber.third - 3] -
           combos.fourth[lottoNumber.fourth - 4] +
           combos.fifth[lottoNumber.fifth - 5];
}

void calcNumbers(int position, LottoCombos combos, LottoNumber *lottoNumber)
{
    // This function is the first attempt to figure out the lotto number combination from the
    // position within the number associated with the combination. It takes >2.5 seconds to complete
    // for all combinations

    int firstPos, secondPos, thirdPos, fourthPos, fifthPos;
    int indx;

    for (indx = 0; indx < MAX_COLUMN_ARRAY; indx++)
    {
        if (position <= combos.first[indx])
        {
            firstPos = combos.first[indx];
            lottoNumber->first = indx + 1;
            if (firstPos == 1)
            {
                lottoNumber->second = lottoNumber->first + 1;
                lottoNumber->third = lottoNumber->first + 2;
                lottoNumber->fourth = lottoNumber->first + 3;
                lottoNumber->fifth = lottoNumber->first + 4;
                return;
            }
        }
        else
        {
            break;
        }
    }

    for (indx -= 1; indx < MAX_COLUMN_ARRAY; indx++)
    {
        if (position > (firstPos - combos.second[indx]))
        {
            secondPos = combos.second[indx];
            lottoNumber->second = indx + 2;
            if (secondPos == 1)
            {
                lottoNumber->third = lottoNumber->second + 1;
                lottoNumber->fourth = lottoNumber->second + 2;
                lottoNumber->fifth = lottoNumber->second + 3;
                return;
            }
        }
        else
        {
            break;
        }
    }

    for (indx -= 1; indx < MAX_COLUMN_ARRAY; indx++)
    {
        if (position <= (firstPos - secondPos + combos.third[indx]))
        {
            thirdPos = combos.third[indx];
            lottoNumber->third = indx + 3;
            if (thirdPos == 1)
            {
                lottoNumber->fourth = lottoNumber->third + 1;
                lottoNumber->fifth = lottoNumber->third + 2;
                return;
            }
        }
        else
        {
            break;
        }
    }

    for (indx -= 1; indx < MAX_COLUMN_ARRAY; indx++)
    {
        if (position > (firstPos - secondPos + thirdPos - combos.fourth[indx]))
        {
            fourthPos = combos.fourth[indx];
            lottoNumber->fourth = indx + 4;
            if (fourthPos == 1)
            {
                lottoNumber->fifth = lottoNumber->fourth + 1;
                return;
            }
        }
        else
        {
            break;
        }
    }

    for (indx -= 1; indx < MAX_COLUMN_ARRAY; indx++)
    {
        if (position <= (firstPos - secondPos + thirdPos - fourthPos + combos.fifth[indx]))
        {
            lottoNumber->fifth = indx + 5;
        }
    }
}

void sortRandomNumbers(int *randomNumbers)
{
    int indx = 0;
    int value;

    value = *(randomNumbers);
    for (int j = 1; j < 5; j++)
    {
        if (value > *(randomNumbers + j))
        {
            *(randomNumbers + j - 1) = *(randomNumbers + j);
            *(randomNumbers + j) = value;
        }
        else
            return;
    }
}

void printBits(char a)
{
    int i;

    for (i = 7; i >= 0; i--)
    {
        if ((a & (1 << i)) != 0)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

BinaryTreeNode *createNewNode()
{
    BinaryTreeNode *node = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    node->position = 0;
    node->number = 0;
    node->right = NULL;
    node->left = NULL;

    return node;
}

void setNode(BinaryTreeNode *node, uint32_t position, uint8_t number)
{
    node->position = position;
    node->number = number;
}

BinaryTreeNode *buildBinaryTree(uint32_t column[], uint8_t beginElement, uint8_t endElement, uint8_t columnOffset)
{
    BinaryTreeNode *node = createNewNode();
    if (beginElement == endElement)
    {
        setNode(node, column[beginElement], beginElement + columnOffset);
    }
    else
    {
        int middleElement = beginElement + ((endElement - beginElement) / 2);
        setNode(node, column[middleElement], middleElement + columnOffset);
        if (endElement - beginElement != 1)
            node->right = buildBinaryTree(column, beginElement, middleElement - 1, columnOffset);
        node->left = buildBinaryTree(column, middleElement + 1, endElement, columnOffset);
    }

    return node;
}

void traverseTree(BinaryTreeNode *node, int level, char *nodeType)
{
    for (int i = 0; i < level; i++)
        printf("\t");
    printf("%-5s Number:%2d Position:%8d\n", nodeType, node->number, node->position);
    level++;
    if (node->right != NULL)
        traverseTree(node->right, level, "Right");
    if (node->left != NULL)
        traverseTree(node->left, level, "Left");
}

BinaryTreeNode *getNode(BinaryTreeNode *root, int searchValue)
{
    // This function is no longer used

    BinaryTreeNode *node;

    if (searchValue == root->position)
        return root;

    if (root->left == NULL && root->right == NULL)
    {
        if (searchValue < root->position)
            return root;

        return NULL;
    }

    if (searchValue < root->position)
    {
        if (root->left == NULL)
            return NULL;

        node = getNode(root->left, searchValue);
    }

    if (searchValue > root->position)
    {
        if (root->right == NULL)
            return NULL;

        node = getNode(root->right, searchValue);
    }

    if (node == NULL && searchValue < root->position)
        node = root;

    return node;
}

BinaryTreeNode *findNumberGTE(BinaryTreeNode *bst, int searchValue)
{
    // This function is no longer used

    BinaryTreeNode *foundNode = NULL;

    if (bst->position == searchValue)
        return bst;

    if (bst->position > searchValue && bst->left != NULL)
    {
        foundNode = findNumberGTE(bst->left, searchValue);
    }

    if (bst->position < searchValue && bst->right != NULL)
    {
        foundNode = findNumberGTE(bst->right, searchValue);
    }

    if (foundNode == NULL && bst->position > searchValue)
        foundNode = bst;

    return foundNode;
}

BinaryTreeNode *findNumberGT(BinaryTreeNode *bst, int searchValue)
{
    // This function is no longer used

    BinaryTreeNode *foundNode = NULL;

    if (bst->position > searchValue && bst->left != NULL)
    {
        foundNode = findNumberGT(bst->left, searchValue);
    }

    if (bst->position <= searchValue && bst->right != NULL)
    {
        foundNode = findNumberGT(bst->right, searchValue);
    }

    if (foundNode == NULL && bst->position > searchValue)
        foundNode = bst;

    return foundNode;
}

BinaryTreeNode *findNodeGT(BinaryTreeNode *bst, int searchValue, bool gteFlag)
{
    BinaryTreeNode *foundNode = NULL;

    if (gteFlag == true && bst->position == searchValue)
        return bst;

    if (bst->position > searchValue && bst->left != NULL)
    {
        foundNode = findNodeGT(bst->left, searchValue, gteFlag);
    }

    if (bst->position <= searchValue && bst->right != NULL)
    {
        foundNode = findNodeGT(bst->right, searchValue, gteFlag);
    }

    if (foundNode == NULL && bst->position > searchValue)
        foundNode = bst;

    return foundNode;
}

void initializeLottoCombos(LottoCombos *combos)
{
    int firstNum, secondNum, thirdNum, fourthNum, fifthNum;

    for (int column = 0; column < MAX_COLUMN_ARRAY; column++)
    {
        firstNum = MAX_VALUE - column;
        secondNum = MAX_VALUE - column - 1;
        thirdNum = MAX_VALUE - column - 2;
        fourthNum = MAX_VALUE - column - 3;
        fifthNum = MAX_VALUE - column - 4;

        combos->first[column] = firstNum * secondNum * thirdNum * fourthNum * fifthNum / FIVE_NUMBER_DIVISOR;
        combos->second[column] = secondNum * thirdNum * fourthNum * fifthNum / FOUR_NUMBER_DIVISOR;
        combos->third[column] = thirdNum * fourthNum * fifthNum / THREE_NUMBER_DIVISOR;
        combos->fourth[column] = fourthNum * fifthNum / TWO_NUMBER_DIVISOR;
        combos->fifth[column] = fifthNum;

        // printf("%8d:%8d:%8d:%8d:%8d\n", combos->first[column], combos->second[column], combos->third[column],
        //        combos->fourth[column], combos->fifth[column]);
    }
}

int main()
{
    int counter = 0;
    int calcPos = 0;
    int bitPosition;
    uint8_t byteArray[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    uint8_t *foundNumberArray;
    clock_t start = clock();
    clock_t diff;

    LottoCombos lottoCombo;
    LottoBST lottoBST;
    LottoNumber lottoNumber;

    foundNumberArray = (uint8_t *)malloc(MAX_ARRAY);
    // for (int x = 0; x < MAX_ARRAY; x++)
    // {
    //     foundNumberArray[x] = 0x88;
    // }
    initializeLottoCombos(&lottoCombo);
    lottoBST.first = buildBinaryTree(lottoCombo.first, 0, MAX_COLUMN_ARRAY - 1, 1);
    // traverseTree(lottoBST.first, 0, "Root");
    lottoBST.second = buildBinaryTree(lottoCombo.second, 0, MAX_COLUMN_ARRAY - 1, 2);
    // traverseTree(lottoBST.second, 0, "Root");
    lottoBST.third = buildBinaryTree(lottoCombo.third, 0, MAX_COLUMN_ARRAY - 1, 3);
    // traverseTree(lottoBST.third, 0, "Root");
    lottoBST.fourth = buildBinaryTree(lottoCombo.fourth, 0, MAX_COLUMN_ARRAY - 1, 4);
    // traverseTree(lottoBST.fourth, 0, "Root");
    lottoBST.fifth = buildBinaryTree(lottoCombo.fifth, 0, MAX_COLUMN_ARRAY - 1, 5);
    // traverseTree(lottoBST.fifth, 0, "Root");
    for (int first = 1; first <= MAX_VALUE - 4; first++)
    {
        for (int second = first + 1; second <= MAX_VALUE - 3; second++)
        {
            for (int third = second + 1; third <= MAX_VALUE - 2; third++)
            {
                for (int fourth = third + 1; fourth <= MAX_VALUE - 1; fourth++)
                {
                    for (int fifth = fourth + 1; fifth <= MAX_VALUE; fifth++)
                    {
                        counter++;
                        // LottoNumber lottoNum = {first, second, third, fourth, fifth};
                        // calcPos = calcPosition(lottoCombo, lottoNum);
                        // printf("%8d", counter);
                        // printf("    %2d:%2d:%2d:%2d:%2d   %8d", lottoNum.first, lottoNum.second, lottoNum.third,
                        //        lottoNum.fourth, lottoNum.fifth, calcPos);
                        // printf("    %8d:%8d:%8d:%8d:%8d\n", lottoCombo.first[first - 1], lottoCombo.second[second - 2],
                        //        lottoCombo.third[third - 3], lottoCombo.fourth[fourth - 4], lottoCombo.fifth[fifth - 5]);
                        // for (int mega = 0; mega < 25; mega++)
                        // {
                        //     bitPosition = calcPos * 25 + mega;
                        //     if (*(numberArray + bitPosition / 8) & byteArray[bitPosition % 8])
                        //         printf("%d:%d:%d:%d\n", bitPosition, bitPosition / 8, bitPosition % 8, *(numberArray + bitPosition / 8) & byteArray[bitPosition % 8]);
                        // }
                    }
                }
            }
        }
    }

    for (int pos = 1; pos <= counter; pos++)
    {
        int num1, num2, num3, num4, num5, searchValue;
        BinaryTreeNode *node;

        searchValue = pos;
        node = findNodeGT(lottoBST.first, searchValue, true);
        num1 = node->number;
        searchValue = node->position - pos;
        node = findNodeGT(lottoBST.second, searchValue, false);
        num2 = node->number;
        searchValue -= node->position;
        node = findNodeGT(lottoBST.third, abs(searchValue), true);
        num3 = node->number;
        searchValue += node->position;
        node = findNodeGT(lottoBST.fourth, abs(searchValue), false);
        num4 = node->number;
        searchValue -= node->position;
        node = findNodeGT(lottoBST.fifth, abs(searchValue), true);
        num5 = node->number;
        // printf("%2d:%2d:%2d:%2d:%2d", num1, num2, num3, num4, num5);
        // calcNumbers(pos, lottoCombo, &lottoNumber);
        // printf("  %2d:%2d:%2d:%2d:%2d\n", lottoNumber.first, lottoNumber.second, lottoNumber.third, lottoNumber.fourth, lottoNumber.fifth);
    }

    // long long totalCombos = 70;
    // long long duplicates = 0;
    // time_t seed;
    // int randValue, randNum[5];
    // int mega;
    // int dup, indx;
    // struct timespec ts;

    // for (int i = 1; i < 5; i++)
    // {
    //     totalCombos *= MAX_VALUE - i;
    // }
    // totalCombos *= 25;
    // totalCombos /= 120;

    // timespec_get(&ts, TIME_UTC);
    // srandom(ts.tv_nsec ^ ts.tv_sec);

    // // srand((unsigned)time(&seed));
    // // while (totalCombos > 0)
    // for (int loop = 0; loop < 10;)
    // {
    //     for (indx = 0; indx < 5; indx++)
    //     {
    //         randNum[indx] = 0;
    //     }
    //     mega = 0;

    //     while (randNum[0] == 0)
    //     {
    //         // randValue = (rand() % MAX_VALUE) + 1;
    //         randValue = random() % MAX_VALUE + 1;
    //         for (indx = 0, dup = 0; indx < 5; indx++)
    //         {
    //             if (randNum[indx] == randValue)
    //                 dup = 1;
    //         }
    //         if (dup == 0)
    //             randNum[0] = randValue;
    //         sortRandomNumbers(&randNum[0]);
    //     }
    //     mega = (rand() % 25) + 1;
    //     calcPos = calcPosition(randNum[0], randNum[1], randNum[2], randNum[3], randNum[4]);
    //     bitPosition = calcPos * 25 + mega;
    //     if (!(*(numberArray + bitPosition / 8) & byteArray[bitPosition % 8]))
    //     {
    //         // printf("Before - ");
    //         // printBits(*(numberArray + bitPosition / 8));
    //         // printBits(byteArray[bitPosition % 8]);
    //         *(numberArray + bitPosition / 8) = *(numberArray + bitPosition / 8) | byteArray[bitPosition % 8];
    //         // printf("After - ");
    //         // printBits(*(numberArray + bitPosition / 8));
    //         totalCombos--;
    //         printf("%2d:%2d:%2d:%2d:%2d:%2d\n", randNum[0], randNum[1], randNum[2], randNum[3], randNum[4], mega);
    //         loop++;
    //     }
    //     else
    //         duplicates++;
    // }

    // printf("Duplicates %lld\n", duplicates);

    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Elapsed %d seconds %d milliseconds\n", msec / 1000, msec % 1000);

    return 0;
}

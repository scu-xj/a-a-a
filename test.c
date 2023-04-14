#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define TOTAL_MEMORY 200
typedef struct partition {
int num; //分区号
int startAdress; //分区开始地址
int leisureAdress; //空闲地址
int size; //剩余空间
int state; //状态, 0 未分配，1 已分配
struct partition *next;
}partition, *PART;
void printPartitionQue(PART partHead) {
PART mPart = partHead;
printf("分区号 起址 空闲起址 空闲空间 状态\n");
while (mPart != NULL) {
printf("%3d ", mPart->num);
printf("%3d ", mPart->startAdress);
printf("%3d ", mPart->leisureAdress);
printf("%3d ", mPart->size);
printf("%3d ", mPart->state);
printf("\n");
mPart = mPart->next;
}
printf("\n");
}
/**
* 创建分区
*/
PART createPartition() {
PART partHead = NULL, mPart = NULL;
int sizes[4] = { 64, 16, 128, 32 };
int startAdress = 20;
 int i;
for (i = 1; i <= 4; i++) {
if (i == 1) {
mPart = partHead = (PART)malloc(sizeof(partition));
mPart->num = i;
mPart->startAdress = startAdress;
mPart->leisureAdress = startAdress;
mPart->size = sizes[i - 1];
mPart->state = 0;
startAdress += mPart->size;
mPart->next = NULL;
}
else {
mPart->next = (PART)malloc(sizeof(partition));
mPart = mPart->next;
mPart->num = i;
mPart->startAdress = startAdress;
mPart->leisureAdress = startAdress;
mPart->size = sizes[i - 1];
mPart->state = 0;
startAdress += mPart->size;
mPart->next = NULL;
} }
return partHead;
}
/**
* 可用空间大小按升序排序
*/
PART sort(PART partHead, int totalPart) {
PART sortHead = NULL;
PART nPart = NULL, tPart = NULL;;
PART temp;
int min = 0;
while (totalPart != 0) {
min = partHead->size;
nPart = partHead->next;
//获取最小的大小赋值给 min 
while (nPart != NULL) {
if (min > nPart->size) min = nPart->size;
nPart = nPart->next;
}
nPart = partHead;
while (nPart != NULL) {
if (nPart->size == min) {
temp = nPart;
if (sortHead == NULL) {
tPart = sortHead = (PART)malloc(sizeof(partition));
tPart->num = nPart->num;
tPart->startAdress = nPart->startAdress;
tPart->leisureAdress = nPart->leisureAdress;
tPart->size = nPart->size;
tPart->state = nPart->state;
tPart->next = NULL;
}
else {
tPart->next = (PART)malloc(sizeof(partition));
tPart = tPart->next;
tPart->num = nPart->num;
tPart->startAdress = nPart->startAdress;
tPart->leisureAdress = nPart->leisureAdress;
tPart->size = nPart->size;
tPart->state = nPart->state;
tPart->next = NULL;
}
PART mPart = partHead;
while (mPart != NULL) {
if (mPart == temp) {
partHead = partHead->next;
totalPart--;
break;
}
else if (mPart->next == temp) {
mPart->next = temp->next;
totalPart--;
break;
}
mPart = mPart->next;
} }
nPart = nPart->next;
} }
return sortHead;
}
/**
* 首次适应算法
*/
void assignOfFirstFit(PART partHead, PART mPart, int size) {
mPart = partHead;
while (mPart != NULL) {
if (mPart->size >= size) {
mPart->size -= size;
mPart->leisureAdress += size;
mPart->state = 1;
printf("*********************** 成 功 分 配 后 的 分 区 列 表
***********************\n");
printPartitionQue(partHead);
break;
}
mPart = mPart->next;
}
if (mPart == NULL) printf("内存不足!\n");
}
/**
* 循环首次适应算法
*/
PART assignOfNextFit(PART partHead, PART mPart, int size, int totalPart) {
while (totalPart != 0) {
if (mPart != NULL) {
if (mPart->size >= size) {
mPart->size -= size;
mPart->leisureAdress += size;
mPart->state = 1;
printf("*********************** 成 功 分 配 后 的 分 区 列 表
***********************\n");
printPartitionQue(partHead);
return mPart->next;
}
mPart = mPart->next;
totalPart--; }
else mPart = partHead;
}
if (totalPart == 0) {
printf("内存不足!\n");
return mPart;
} }
// 最佳适应算法
PART assignOfBestFit(PART partHead, PART mPart, int size) {
mPart = sort(partHead, 4);
partHead = mPart;
while (mPart != NULL) {
if (mPart->size >= size) {
mPart->size -= size;
mPart->leisureAdress += size;
mPart->state = 1;
printf("*********************** 成 功 分 配 后 的 分 区 列 表
***********************\n");
partHead = sort(partHead, 4);
printPartitionQue(partHead);
return partHead;
}
mPart = mPart->next;
}
if (mPart == NULL) {
printf("内存不足!\n");
return partHead;
} }
/**
* 分配内存
*/
void assignMemory(PART partHead, int assignType) {
int totalPart = 4;
PART mPart = partHead;
char c;
char name[10] = "";
int size = 0;
printf("是否输入作业(Y/N)：");
scanf("%c", &c);
while (c == 'Y' || c == 'y') {
printf("请输入作业名：");
scanf("%s", name);
printf("请输入作业大小：");
scanf("%d", &size);
switch (assignType) {
case 1:
assignOfFirstFit(partHead, mPart, size);
break;
case 2:
partHead = assignOfBestFit(partHead, mPart, size);
break;
}
printf("是否输入作业(Y/N)：");
getchar();
scanf("%c", &c);
} }
/**
* 最佳适应算法
*/
void BestFit(PART partHead) {
printf("***********************排序前的分区列表***********************\n");
printPartitionQue(partHead);
//分配内存
assignMemory(partHead, 2);
}
/**
* 首次适应算法
*/
void FirstFit(PART partHead) {
printf("***********************分配前的分区列表***********************\n");
printPartitionQue(partHead);
//分配内存
assignMemory(partHead, 1);
}
int main() {
int k;
PART partHead = createPartition();
printf("***************************** 动 态 分 区 分 配 方 式 的 模 拟
*************************");
printf("\n 1 、 首 次 适 应 算 法 
");
printf("\n 2 、 最 佳 适 应 算 法 
");
printf("\n 3 、退出 
");
printf("\n 请输入对应序号选择相应的算法：");
scanf("%d", &k);
getchar();
switch (k) {
case 1:
FirstFit(partHead);
break;
case 2:
BestFit(partHead);
break;
case 3:
break;
default:
printf("选择错误，请重新选择。");
}
return 0;
}

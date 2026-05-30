#include<stdio.h>

int main()
{
    int amount=100;
    int price=0;
    
    printf("请输入金额（元）：");
    scanf("%d",&price);

    printf("请输入面额（元）；");
    scanf("%d",&amount);

    int change=amount-price;/*这里change的定义居然不可以放代码开头*/
    printf("找你%d\n",change);/*这里change前面居然没有”&*/

    return 0;
}
//
//  CommonEnum.h
//  AnimalAid
//
//  Created by Student_17 on 14-11-3.
//
//

#ifndef __AnimalAid__CommonEnum__
#define __AnimalAid__CommonEnum__

/* 动物出来的位置 */
typedef enum{
    lowPoint = 1,
    middlePoint = 2,
    hightPoint = 3
} BeginLocation;

/* 基本木板的类型 */
typedef enum {
    normalType,
    typeOne,
    typeTwo,
    typeThree,
    typeFour,
    typeFive
}BoardType;

/* 粒子特效的类型 */
typedef enum {
    leafPartical,
    snowPartical
}ParticalType;

#endif /* defined(__AnimalAid__CommonEnum__) */

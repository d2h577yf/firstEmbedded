#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>
#include "font.h"  // 假设 font.h 是你用于显示字符的头文件
#include "oled.h"

// 定义字符在 OLED 上的初始位置
#define INITIAL_X 0
#define INITIAL_Y 0

// 定义移动状态
typedef struct {
    float x;                   // 当前 X 位置
    float y;                   // 当前 Y 位置
    float velocity_x;          // X 方向速度
    float velocity_y;          // Y 方向速度
    float acceleration_x;      // X 方向加速度
    float acceleration_y;      // Y 方向加速度
    float lateral_acceleration; // 横向加速度
    float vertical_acceleration; // 纵向加速度
    float max_velocity;        // 最大速度
    float friction;            // 阻力（用于模拟减速）
} MoveData;

// 函数声明
void Move_Init(MoveData* move_data);
void Move_Update(MoveData* move_data, uint16_t adc1_value, uint16_t adc2_value, float delta_time,const Font* font);
void Move_Render(const MoveData* move_data, const Font* font, OLED_ColorMode color);

float Get_Velocity_X(const MoveData* move_data);
float Get_Velocity_Y(const MoveData* move_data);
float Get_Displacement_X(const MoveData* move_data);
float Get_Displacement_Y(const MoveData* move_data);
float Get_Acceleration_X(const MoveData* move_data);
float Get_Acceleration_Y(const MoveData* move_data);
float Get_Drag(const MoveData* move_data);

#endif // MOVE_H


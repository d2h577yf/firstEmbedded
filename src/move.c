#include "move.h"
#include "oled.h" 
#include "font.h" // 假设 oled.h 是你用于 OLED 显示的头文件

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

// 定义初始位置
#define INITIAL_X 64
#define INITIAL_Y 32
#define DRAG_COEFFICIENT 0.1f 

// 初始化移动数据
void Move_Init(MoveData* move_data) {
    move_data->x = INITIAL_X;               // 初始化 X 位置
    move_data->y = INITIAL_Y;               // 初始化 Y 位置
    move_data->velocity_x = 0.0f;           // 初始化 X 方向速度
    move_data->velocity_y = 0.0f;           // 初始化 Y 方向速度
    move_data->acceleration_x = 0.0f;       // 初始化 X 方向加速度
    move_data->acceleration_y = 0.0f;       // 初始化 Y 方向加速度
    move_data->lateral_acceleration = 0.0f; // 初始化横向加速度
    move_data->vertical_acceleration = 0.0f; // 初始化纵向加速度

    move_data->max_velocity = 1500.0f;        // 设置最大速度（根据需要调整）
    move_data->friction = 0.95f;            // 设置阻力（例如，0.95表示每次更新后速度减少5%）
}

void Move_Update(MoveData* move_data, uint16_t adc1_value, uint16_t adc2_value, float delta_time,const Font* font) {
    // 根据 ADC 值更新加速度
    move_data->acceleration_x = (adc1_value / 4096.0f) * 10.0f - 5.0f;
    move_data->acceleration_y = (adc2_value / 4096.0f) * 10.0f - 5.0f;

    // 更新速度
    move_data->velocity_x += move_data->acceleration_x * delta_time;
    move_data->velocity_y += move_data->acceleration_y * delta_time;

    // 应用阻力（速度逐渐减少）
    move_data->velocity_x *= move_data->friction;
    move_data->velocity_y *= move_data->friction;

    // 限制速度不超过最大速度
    if (move_data->velocity_x > move_data->max_velocity) {
        move_data->velocity_x = move_data->max_velocity;
    } else if (move_data->velocity_x < -move_data->max_velocity) {
        move_data->velocity_x = -move_data->max_velocity;
    }
    
    if (move_data->velocity_y > move_data->max_velocity) {
        move_data->velocity_y = move_data->max_velocity;
    } else if (move_data->velocity_y < -move_data->max_velocity) {
        move_data->velocity_y = -move_data->max_velocity;
    }

    // 更新位置
    move_data->x += move_data->velocity_x * delta_time;
    move_data->y += move_data->velocity_y * delta_time;

    // 确保位置在 OLED 显示范围内（边界检查）
    if (move_data->x > OLED_WIDTH - font->w) {
        move_data->x = OLED_WIDTH - font->w;
    } else if (move_data->x < 0) {
        move_data->x = 0;
    }
    if (move_data->y > OLED_HEIGHT - font->h) {
        move_data->y = OLED_HEIGHT - font->h;
    } else if (move_data->y < 0) {
        move_data->y = 0;
    }
}


void Move_Render(const MoveData* move_data, const Font* font, OLED_ColorMode color) {
    // 在 OLED 上绘制字符，假设你有一个要绘制的字符，例如 'A'
    char character = 'W'; // 这里可以是你要显示的字符
    OLED_PrintString(move_data->x, move_data->y, &character, font, color);
}

float Get_Velocity_X(const MoveData* move_data) {
    return move_data->velocity_x;
}

float Get_Velocity_Y(const MoveData* move_data) {
    return move_data->velocity_y;
}

// 获取位移
float Get_Displacement_X(const MoveData* move_data) {
    return move_data->x;
}

float Get_Displacement_Y(const MoveData* move_data) {
    return move_data->y;
}

// 获取加速度
float Get_Acceleration_X(const MoveData* move_data) {
    return move_data->acceleration_x;
}

float Get_Acceleration_Y(const MoveData* move_data) {
    return move_data->acceleration_y;
}

// 获取阻力大小
float Get_Drag(const MoveData* move_data) {
    return DRAG_COEFFICIENT * (move_data->velocity_x + move_data->velocity_y); // 这里假设阻力和速度成正比
}
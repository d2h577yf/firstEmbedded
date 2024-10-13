#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdint.h>

// 系统的不同模式
typedef enum {
    MENU_MODE,    // 主菜单模式
    MODE_1,       // 模式1
    MODE_2,       // 模式2
    MODE_3,       // 模式3
    NUM_MODES     // 模式数量
} SystemState;

// 函数声明
void StateMachine_Init(void);    // 初始化状态机
void StateMachine_Update(void);  // 更新状态机，检测并切换状态
SystemState Get_CurrentState(void);  // 获取当前状态

// 每个模式的函数声明
void Mode1_Function(void);
void Mode2_Function(void);
void Mode3_Function(void);

#endif // STATE_MACHINE_H

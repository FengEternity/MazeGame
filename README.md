# MazeGame

这是一个用C++开发的迷宫小游戏，具有图形界面和背景音乐。玩家可以选择不同的难度和模式（玩家玩或电脑玩），并通过键盘或自动移动来完成迷宫。

程序运行截图如下，

<img width="601" alt="image" src="https://github.com/FengEternity/MazeGame/assets/114133472/a25b2f0f-d96a-45ae-a489-fdc02ea04d93">
<img width="500" alt="image" src="https://github.com/FengEternity/MazeGame/assets/114133472/dd98404b-c672-4826-a64c-b4e4de1b45ed">

## 功能

- 选择模式：玩家玩或电脑玩
- 选择难度：简单、中等、困难
- 玩家通过键盘控制移动
- 电脑自动探索迷宫
- 背景音乐和音效
- 显示胜利信息
- 保存和加载迷宫

## 依赖

- Windows系统
- EasyX库
- winmm.lib库（用于音效播放）

## 安装和运行

1. 克隆或下载本仓库到你的本地机器。
2. 确保安装了EasyX库并正确配置。
3. 使用支持C++的IDE（如Visual Studio）打开项目。
4. 编译并运行项目。

## 代码结构

- `main.cpp`：主程序，负责游戏的初始化和主循环。
- `Maze.h` 和 `Maze.cpp`：定义和实现了迷宫类，包括迷宫的生成和绘制。
- `Player.h` 和 `Player.cpp`：定义和实现了玩家类，包括玩家的移动和绘制。
- `UI.h` 和 `UI.cpp`：定义和实现了用户界面类，包括开始界面的绘制和按钮点击检测。
- `Common.h`：定义了一些通用的枚举和常量。

## 操作说明

- 运行程序后，首先进入开始界面。
- 通过点击按钮选择模式（玩家玩或电脑玩）和难度（简单、中等、困难）。
- 点击“开始游戏”按钮进入游戏。
- 在玩家模式下，通过键盘的方向键（WASD）控制玩家移动。
- 在电脑模式下，玩家自动移动。
- 到达迷宫终点后显示胜利信息。
- 胜利后可选择重新开始、回到首页或退出游戏。

## 示例代码

```cpp
// 主程序示例
int main() {
    // 初始化图形界面，设置窗口大小
    initgraph(width, height);
    UI ui(width, height);

    // 主循环处理游戏逻辑
    while (true) {
        // 显示游戏开始界面并处理用户选择
        while (goToStart || (!playerSelected || !difficultySelected)) {
            cleardevice();
            ui.drawStartUI(playerSelected, difficultySelected, playerMode, difficulty);
            FlushBatchDraw();

            // 检测鼠标点击，更新状态
            // ...
        }

        // 根据选择的难度调整窗口大小
        // ...

        // 初始化迷宫和玩家
        Maze maze(rows, cols, difficulty);
        maze.generateMaze(1, 1);
        Player player(maze, 1, 1);

        // 绘制迷宫和玩家
        // ...

        // 主游戏循环
        while (true) {
            cleardevice();
            maze.drawMaze();
            player.drawPlayer();

            // 处理玩家移动或电脑自动移动
            // ...

            if (player.isAtEnd()) {
                // 显示胜利信息
                break;
            }

            FlushBatchDraw();
            Sleep(50);
        }

        // 等待用户选择重玩或退出
        // ...
    }

    closegraph();
    return 0;
}



# 许可证

此项目使用 MIT 许可证 - 详情请参阅 [LICENSE](LICENSE) 文件。


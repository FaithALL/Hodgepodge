from enum import Enum

# 帧数
FPS = 60

# 窗口大小
WINDOW_WIDTH = 378
WINDOW_HEIGHT = 680

# 颜色
BACKGROUND_COLOR = (250, 255, 250)
PLAYER_COLOR = (0, 0, 0)
COLORS = (
    [140, 188, 255],
    [149, 93, 182],
    [238, 92, 66],
    [232, 219, 34],
    [139, 232, 146]
)

# 玩家方块大小
PLAYER_LEN = 15

# 矩形障碍物
PIPE_HEIGHT = 36
PIPE_GAP_LEN = 128
PIPE_GAP_X = (0 + 30, WINDOW_WIDTH - PIPE_GAP_LEN - 30)

# 正方形障碍物
BLOCK_LEN = 25
BLOCK_AREA_WIDTH = (-PIPE_GAP_LEN * 0.4, PIPE_GAP_LEN * 0.4)
BLOCK_AREA_HEIGHT = (PIPE_GAP_LEN * 0.6, PIPE_GAP_LEN * 0.8)

# 物理参数
GRAVITY = 0.25
ACC_X = 1.0
ACC_Y = 8.5


# 动作
class ACTION(Enum):
    NOTHING = 0
    LEFT = 1
    RIGHT = 2

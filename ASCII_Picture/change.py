import cv2
import os
import math

# ===================== 可自定义的参数（改这里！）=====================
VIDEO_PATH = "video2.mp4"  # 你的原视频路径（比如放在PyCharm项目根目录）
OUTPUT_DIR = "video2_frames"  # 帧图片输出文件夹（自动创建）
TARGET_FPS = 15  # 抽取帧率（3秒=45帧，建议15）
TARGET_RESOLUTION = (640, 360)  # 16:9目标分辨率（640×360/854×480可选）
IMAGE_FORMAT = "jpg"  # 输出格式（固定jpg，不要改png）


# ===================== 核心抽帧逻辑 =====================
def extract_video_frames():
    # 1. 创建输出文件夹
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)
        print(f"创建输出文件夹：{OUTPUT_DIR}")

    # 2. 打开视频
    cap = cv2.VideoCapture(VIDEO_PATH)
    if not cap.isOpened():
        print("无法打开视频，请检查路径是否正确！")
        return

    # 3. 获取原视频信息
    original_fps = cap.get(cv2.CAP_PROP_FPS)  # 原视频帧率
    total_frames_original = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))  # 原视频总帧数
    video_duration = total_frames_original / original_fps  # 原视频时长（秒）
    print(f"原视频信息：")
    print(f"帧率：{original_fps:.1f} FPS | 总帧数：{total_frames_original} | 时长：{video_duration:.1f} 秒")

    # 4. 计算抽帧间隔（保证抽取TARGET_FPS帧/秒）
    frame_interval = max(1, math.floor(original_fps / TARGET_FPS))
    target_total_frames = int(video_duration * TARGET_FPS)  # 目标总帧数
    print(f"抽帧配置：")
    print(f"目标帧率：{TARGET_FPS} FPS | 抽帧间隔：每{frame_interval}帧抽1帧 | 预计输出帧数：{target_total_frames}")

    # 5. 逐帧抽取+缩放（保证16:9）
    frame_count = 0  # 已抽取的帧数
    current_frame_idx = 0  # 原视频当前帧索引
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break  # 视频读取完毕

        # 按间隔抽帧
        if current_frame_idx % frame_interval == 0:
            # 缩放帧到目标分辨率（保持16:9，避免变形）
            frame_resized = cv2.resize(frame, TARGET_RESOLUTION, interpolation=cv2.INTER_AREA)

            # 命名格式：frame_0001.jpg（补零，保证顺序）
            frame_name = f"frame_{frame_count + 1:04d}.{IMAGE_FORMAT}"
            frame_path = os.path.join(OUTPUT_DIR, frame_name)

            # 保存帧（JPG压缩，体积小）
            cv2.imwrite(frame_path, frame_resized, [cv2.IMWRITE_JPEG_QUALITY, 85])  # 85是压缩质量（1-100，越高越清晰）

            frame_count += 1
            print(f"已抽取：{frame_name}（{frame_count}/{target_total_frames}）", end="\r")

        current_frame_idx += 1

    # 6. 收尾+体积预估
    cap.release()
    cv2.destroyAllWindows()
    print(f"\n抽帧完成！共抽取 {frame_count} 帧，保存至：{OUTPUT_DIR}")

    # 预估总大小（按单帧平均60KB算）
    estimated_size_mb = (frame_count * 60) / 1024
    print(f"体积预估：≈{estimated_size_mb:.2f} MB（远低于200MB限制）")


if __name__ == "__main__":
    extract_video_frames()
from moviepy import VideoFileClip
import os

# ===================== 可自定义参数（改这里！）=====================
VIDEO_PATH = "video2.mp4"  # 你的原视频路径（和抽帧的视频一致）
OUTPUT_WAV_PATH = "video2_audio.wav"  # 输出WAV音频路径
TARGET_SAMPLING_RATE = 44100  # WAV标准采样率（44100Hz，音质好且体积适中）


# ===================== 核心提取逻辑 =====================
def extract_audio_to_wav():
    # 1. 校验视频文件是否存在
    if not os.path.exists(VIDEO_PATH):
        print(f"❌ 错误：视频文件不存在 → {VIDEO_PATH}")
        return

    try:
        # 2. 加载视频（仅读取音频流，不加载视频帧，提速）
        print(f"📌 正在加载视频：{VIDEO_PATH}")
        video_clip = VideoFileClip(VIDEO_PATH)

        # 3. 提取音频轨道
        if not video_clip.audio:
            print("❌ 错误：该视频无音频轨道！")
            video_clip.close()
            return
        audio_clip = video_clip.audio

        # 4. 导出为WAV（设置采样率，保证兼容性）
        print(f"📌 正在提取音频 → 输出路径：{OUTPUT_WAV_PATH}")
        print(f"📌 采样率：{TARGET_SAMPLING_RATE} Hz（WAV标准）")
        audio_clip.write_audiofile(
            OUTPUT_WAV_PATH,
            fps=TARGET_SAMPLING_RATE,  # 采样率
            codec="pcm_s16le"  # WAV无损编码（16位PCM，最通用）
        )

        # 5. 释放资源（避免内存泄漏）
        audio_clip.close()
        video_clip.close()

        # 6. 输出结果
        wav_size = os.path.getsize(OUTPUT_WAV_PATH) / 1024 / 1024  # 转MB
        print(f"\n🎉 音频提取完成！")
        print(f"📊 WAV文件大小：{wav_size:.2f} MB（3秒视频≈1.3MB）")
        print(f"📁 文件路径：{os.path.abspath(OUTPUT_WAV_PATH)}")

    except Exception as e:
        print(f"❌ 提取失败：{str(e)}")


if __name__ == "__main__":
    extract_audio_to_wav()
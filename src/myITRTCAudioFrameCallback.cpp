#include "myITRTCAudioFrameCallback.h"

#include <QMessageBox>
#include <QDebug>
#include <QTranslator>
#include <QLocale>

#include "main_window.h"


myITRTCAudioFrameCallback :: myITRTCAudioFrameCallback() {
	audioData = nullptr;
	audioDataSize = 0;
	audioDataPos = 0;
}

myITRTCAudioFrameCallback :: ~myITRTCAudioFrameCallback() {
	if (audioData) {
		delete[] audioData;
		audioData = nullptr;
	}
}

void myITRTCAudioFrameCallback :: onLocalProcessedAudioFrame(TRTCAudioFrame* frame) {
	if (!audioData) {
		QString runPath = QCoreApplication::applicationDirPath();
		QString finalPath = runPath.append("/assets/audio/custom_audio.pcm");
		QFileInfo fileInfo(QDir::toNativeSeparators(finalPath));
		QString resPath = fileInfo.absoluteFilePath();
		QFile file(resPath);
		if (!fileInfo.exists()) {
			return;
		}
		//QFile file("D:/My/TXLiteAVSDK_TRTC_Win_latest/TRTC-API-Example-Qt/debug/assets/audio/custom_audio.pcm");
		if (!file.open(QIODevice::ReadOnly)) {
			qWarning("´ò²»¿ª");
			return;
		}
		QByteArray array = file.readAll();
		file.close();

		int len = array.size() / sizeof(short);
		audioData = new short[len];
		memcpy(audioData, array.data(), array.size());
		audioDataSize = len;
		audioDataPos = 0;
	}

	short* inputData = reinterpret_cast<short*>(frame->data);
	int len = frame->length / sizeof(short);
	for (int i = 0; i < len; i++) {
		inputData[i] = inputData[i] / 2 + audioData[audioDataPos] / 2;
		audioDataPos++;
		if (audioDataPos >= audioDataSize) {
			audioDataPos = 0;
		}
	}
}


#include "TRTCCloudCallback.h"
#include "ITRTCCloud.h"
#include "TRTCTypeDef.h"

class myITRTCAudioFrameCallback : public ITRTCAudioFrameCallback {
private:
	short* audioData;
	int audioDataSize;
	int audioDataPos;

public:
	myITRTCAudioFrameCallback();

	virtual ~myITRTCAudioFrameCallback();

	void onLocalProcessedAudioFrame(TRTCAudioFrame* frame) override;
};
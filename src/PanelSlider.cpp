#include "PanelSlider.h"

using namespace ci;
using namespace ci::app;
using namespace std;

PanelSlider::PanelSlider(BasePanel *parent, std::string labelText, float *value, float minVal, float maxVal) : BasePanel(){
	mLabelText = labelText;
	//boost::to_upper(mLabelText);
	mMin = minVal;
	mMax = maxVal;
	mValue = value;

	bIsDragging = false;
	mBounds.set(0, 0, 200, 30);
	mHandlePos.set(15, 22);
	mHandleHitbox.set(-5, -5, 5, 5);
	mSliderPct = 0.0f;

	// slider boundaries
	mSliderLeft = mBounds.getUpperLeft() + Vec2f(10, 22);
	mSliderRight = mBounds.getUpperRight() + Vec2f(-10, 22);

	parent->registerPanel(this);

	mGlobal = Panel::PanelGlobal::getInstance();

	updateValue(*mValue);
}

void PanelSlider::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds){
	BasePanel::updateBounds(offset, parentBounds);

	mSliderLeft = mBounds.getUpperLeft() + Vec2f(10, 19);
	mSliderRight = mBounds.getUpperRight() + Vec2f(-10, 19);

	updateValue(*mValue);
}

void PanelSlider::updateValue(float val){
	val = math<float>::clamp(val, mMin, mMax);
	*mValue = val;

	mSliderPct = (val - mMin) / (mMax - mMin);
	mHandlePos.x = lerp(mSliderLeft.x, mSliderRight.x, mSliderPct);
}

void PanelSlider::mouseDown(const Vec2i &pos){
	if (mBounds.contains(pos - mOffset)){

		Vec2f localCoord = pos - mOffset;

		if (mHandleHitbox.contains(localCoord - mHandlePos)){
			bIsDragging = true;
			mHandlePos.x = pos.x - mOffset.x;
		}
	}
}

void PanelSlider::mouseDragged(const Vec2i &pos){
	if (bIsDragging){
		mHandlePos.x = ci::math<float>::clamp(pos.x - mOffset.x, mSliderLeft.x, mSliderRight.x);
		mSliderPct = lmap<float>(mHandlePos.x, mSliderLeft.x, mSliderRight.x, 0.0, 1.0);

		*mValue = (mMax - mMin) * mSliderPct + mMin;
	}
}
void PanelSlider::mouseUp(const Vec2i &pos){
	bIsDragging = false;
}

void PanelSlider::draw() {
	gl::pushMatrices(); {
		gl::translate(mOffset);

		gl::pushMatrices(); {
			gl::translate(12, 1);
			mGlobal->renderText(mLabelText + ": " + to_string(*mValue), mBounds.getUpperLeft());
		}gl::popMatrices();

		gl::color(mGlobal->P_SLIDER_COLOR);
		ci::Vec2f lMod(10, 20);
		ci::Vec2f rMod(-10, 20);

		gl::drawLine(mSliderLeft, mSliderRight);

		Rectf handle(-3, -5, 3, 5);
		handle.offset(mHandlePos);
		gl::drawSolidRect(handle);

		//gl::color(mGlobal->P_OUTLINE_COLOR);
		//gl::drawLine(mBounds.getLowerLeft(), mBounds.getLowerRight());
	}gl::popMatrices();
}
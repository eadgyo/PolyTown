#ifndef _IMAGE_H_
#define _IMAGE_H_
class Image;

#include <Windows.h>
#include <GL/glew.h>
#include "SpriteData.h"
#include "Graphics.h"
#include "string.h"
#include "../Constant.h"
#include <assert.h>
#include "../Maths/Vector3D.h"
#include "../Maths/myRectangle.h"
#include "../Maths/sRectangle.h"
#include "../FileManager/FileManager.h"
#include "myColor.h"

class Image
{
public:
	Image();
	Image(Image& image);
    Image(Graphics* graphics, float width, float height, int currentFrame, int cols, std::string textureName);
	Image(Graphics* graphics, float width, float height, int currentFrame, std::string textureName);
	virtual ~Image();
	Image clone();
	void reset();

	bool getIsInitialized();

	// Getter
	const Vector3D getPos() const { return rec.getCenter(); };
	bool getIsRectDisplaying() const;
	const myRectangle& getRectangle() const;
	int getCols() const;
	float getVisible() const;
	int getOrigWidth() const;
	int getOrigHeight() const;
	float getWidth() const;
	float getHeight() const;
	float getX() const;
	float getY() const;
	Vector3D getLeftPos() const;
	float getRadians() const;
	float getRadians(const Vector3D& vec) const;
	float getDegrees() const;
	float getDegrees(const Vector3D& vec) const;
	int getCurrentFrame() const;
	const sRectangle* getSpriteDataRect() const;
	const myColor& getColorFilter() const;
	SpriteData* getSpriteData();
	const bool getFlipV() const;
	const bool getFlipH() const;
	Graphics* getGraphics() const;
	float getScale() const;
    inline bool getIsInitialized() const { return isInitialized; };
	std::string getTextureName() const;
	float getRecWidth() const;
	float getSpriteDataWidth() const;
	myColor getColor() const { return color; };

	// Setter
	void setFrames(int start, int end);
	void setColorFilter(Uint8 r, Uint8 g, Uint8 b) { colorFilter.r = r; colorFilter.g = g; colorFilter.b = b; };
	void setColorFilter(Uint8 a, Uint8 r, Uint8 g, Uint8 b) { colorFilter.a = a; colorFilter.r = r; colorFilter.g = g; colorFilter.b = b; };
	void setColorFilter(myColor colorFilter) { this->colorFilter.r = colorFilter.r;  this->colorFilter.g = colorFilter.g; this->colorFilter.b = colorFilter.b; this->colorFilter.a = colorFilter.a; };
	void setColor(float r, float g, float b) { color.r = r; color.g = g; color.b = b; };
	void setColor(float a, float r, float g, float b) { color.a = a; color.r = r; color.g = g; color.b = b; };
	void setColor(myColor color) { this->color = color; };
	void set(Image& image);
	void setCols(int cols);
	void setIsDisplayingRec(bool isDisplayingRec);
	void setX(float x);
	void setY(float y);
	void setPos(const Vector3D& center);
	void setLeftPos(const Vector3D& left);
	void setDegrees(float degrees);
	void setDegrees(float degrees, const Vector3D& vec);
	void setRadians(float radians, const Vector3D& vec);
	void setRadians(float radians);
	void setScale(float scale, const Vector3D& center);
	void setDegrees(float degrees, const Vector3D& vec, const Vector3D& center);
	void setRadians(float radians, const Vector3D& vec, const Vector3D& center);
	void setPositionX(float x, const Vector3D& vec);
	void setPositionY(float y, const Vector3D& vec);
	void setPosition(const Vector3D& p);
	void setPositionX(float x);
	void setPositionY(float y);
	void setFlipH(bool b, const Vector3D& center);
	void setFlipV(bool b, const Vector3D& center);
	void setVisible(float visible);
	void setSpriteDataRect(sRectangle* rect);
	void setColorFilter(myColor& colorFilter);
	void setFlipH(bool flipHorizontal);
	void setFlipV(bool flipVertical);
	void setFlipHFree(bool flipHorizontal);
	void setFlipVFree(bool flipHorizontal);
	void setScale(float scale);
	void setGraphics(Graphics* g);
	void setSize(int size);
	void setSpriteData(const SpriteData& spriteData);
	void setRec(const myRectangle& rec);
	void setRec(const Form& rec);
	void clearTexture();
	void loadTexture();

	void initialize(Graphics* graphics, float width, float height, int currentFrame,
		mySurface* texture, std::string textureName);
	void initialize(Graphics* graphics, float width, float height, int currentFrame,
		std::string textureName);
	void initialize(Graphics* graphics, float width, float height, int currentFrame, int cols,
			std::string textureName);
	void initialize(Graphics* graphics,	std::string textureName);
	void initialize(Graphics* graphics, mySurface* surface, std::string text);
	void draw();
	void draw(Graphics* g);
	void draw(const Vector3D& translation);
	void draw(Graphics* g, const Vector3D& translation);
	void draw(Graphics* g, const Vector3D& translation, float scale);
	void setCurrentFrame(int current);
	bool hasAlpha();
	void setRect();

	// Transformations
	void translate(const Vector3D& vec);
	void translateX(float vecX);
	void translateY(float vecY);
	void flipH(const Vector3D& center);
	void flipV(const Vector3D& center);
	void scale(float factor, const Vector3D& center);
	void rotateRadians(float radians, const Vector3D& center);
	
	void letDeleting(bool del) { deletion = del; };
	bool getDeleting() { return deletion; };

protected:
	Graphics* graphics;
	SpriteData* spriteData;
	myColor colorFilter;
	myColor color;
	int cols;
	int currentFrame;
	bool isDisplayingRec;

	myRectangle rec;

	bool isInitialized;
	int startFrame;
	int endFrame;
	bool deletion;
};

#endif /* _IMAGE_H_ */

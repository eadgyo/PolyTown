#ifndef _IMAGE_H_
#define _IMAGE_H_
class Image;

#include "string.h"
#include "Graphics.h"
#include "../Constant.h"
#include <assert.h>
#include "SpriteData.h"
#include "../Maths/Vector3D.h"
#include "../Maths/Rectangle.h"
#include "../Maths/sRectangle.h"
#include "../FileManager.h"

class Image
{
public:
	Image();
	Image(Image& image);
	virtual ~Image();
	Image clone();
	void reset();

	bool getIsInitialized();

	// Getter
	const Vector3D getPos() const { return rec.getCenter(); };
	bool getIsRectDisplaying() const;
	const Rectangle& getRectangle() const;
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
	const SDL_Color& getColorFilter() const;
	SpriteData* getSpriteData();
	const bool getFlipV() const;
	const bool getFlipH() const;
	Graphics* getGraphics() const;
	float getScale() const;
	bool getIsInitialized() const;
	std::string getTextureName() const;
	float getRecWidth() const;
	float getSpriteDataWidth() const;

	// Setter
	void setFrames(int start, int end);
	void setColorFilter(float r, float g, float b) { colorFilter.r = r; colorFilter.g = g; colorFilter.b = b; };
	void setColorFilter(float a, float r, float g, float b) { colorFilter.a = a; colorFilter.r = r; colorFilter.g = g; colorFilter.b = b; };
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
	void setColorFilter(SDL_Color& colorFilter);
	void setFlipH(bool flipHorizontal);
	void setFlipV(bool flipVertical);
	void setScale(float scale);
	void setGraphics(Graphics* g);
	void setSize(int size);
	void setSpriteData(const SpriteData& spriteData);
	void setRec(const Rectangle& rec);
	void setRec(const Form& rec);
	void clearTexture();
	void loadTexture();

	void initialize(Graphics* graphics, int width, int height, int cols,
			SDL_Texture* texture, std::string textureName);
	void initialize(Graphics* graphics, int width, int height, int cols,
			std::string textureName);
	void initialize(Graphics* graphics, int width, int height, int currentFrame, int cols,
			std::string textureName);
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

protected:
	Graphics* graphics;
	SpriteData* spriteData;
	SDL_Color colorFilter;
	int cols;
	int currentFrame;
	bool isDisplayingRec;

	Rectangle rec;

	float visible;
	bool isInitialized;
	int startFrame;
	int endFrame;

};

#endif /* _IMAGE_H_ */

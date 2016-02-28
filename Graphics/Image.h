#ifndef _IMAGE_H_
#define _IMAGE_H_
#include "string.h"

class Image
{
public:
	Image();
	Image(const Image& image);
	virtual ~Image();
	Image clone();
	void reset();

	// Getter
	bool getIsRectDisplayin() const;
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
	void setFrames(int start, int end) const;
	float getRadians() const;
	float getRadians(const Vector3D& vec) const;
	float getDegrees() const;
	float getDegrees(const Vector3D& vec);
	int getCurrentFrame();
	const sRectangle& getSpriteDataRect();
	const Color& getColorFilter();
	const SpriteData& getSpriteData();
	const bool getFlipV();
	const bool getFlipH();
	Graphics& getGraphics();
	float getScale();
	bool isInitialized();
	std::string getTextureName();
	float getRecWidth();
	float getSpriteDataWidth();

	// Setter
	void set(const Image& image);
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
	void setSpriteDataRect(sRectangle& rect);
	void setColorFilter(Color& colorFilter);
	void setFlipH(bool flipHorizontal);
	void setFlipV(bool flipVertical);
	void setScale(float scale);
	void setGraphics(Graphics& g);
	void setSize(int size);
	void setSpriteData(const SpriteData& spriteData);
	void setRec(const Rectangle& rec);
	void setRec(const Form& rec);
	void clearTexture();
	void loadTexture();

	void initialize(Graphics graphics, int width, int height, int cols, BufferedImage texture, String textureName);
	void draw();
	void draw(Graphics g);
	void draw(const Vector3D& translation);
	void draw(Graphics g, const Vector3D& translation);
	void draw(Graphics g, const Vector3D& translation, float scale);
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
	void visible(float f);

protected:
	Graphics graphics;
	SpriteData spriteData;
	Color colorFilter;
	int cols;
	int currentFrame;
	boolean isDisplayingRec;

	Rectangle rec;

	float visible;
	boolean isInitialized;
	int startFrame;
	int endFrame;

};

#endif /* _IMAGE_H_ */

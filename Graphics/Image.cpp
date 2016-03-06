/*
 * Image.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: ronan-h
 */

#include "Image.h"

Image::Image()
{
	isDisplayingRec = false;
	visible = 1.0f;
	isInitialized = false;
	spriteData = new SpriteData();
	setColorFilter(0.0f,0.0f,0.0f,0.0f);
}

Image::Image(Image& image)
{
	Image();
	set(image);
}

Image::~Image()
{

}

Image Image::clone()
{
	Image l_image((*this));
	return l_image;
}

void Image::reset()
{
	setFlipV(false);
	setFlipH(false);
	setVisible(1);
	rec.set(Vector3D(true), Vector3D(spriteData->rect->getWidth(), spriteData->rect->getHeight()), 0);
}

///////////////////
//		Get      //
///////////////////
bool Image::getIsRectDisplaying() const
{
	return isDisplayingRec;
}

const Rectangle& Image::getRectangle() const
{
	return rec;
}

int Image::getCols() const
{
	return cols;
}

float Image::getVisible() const
{
	return visible;
}

int Image::getOrigWidth() const
{
	return (int) spriteData->rect->getWidth();
}

int Image::getOrigHeight() const
{
	return (int) spriteData->rect->getHeight();
}

float Image::getWidth() const
{
	return rec.getLength().getX();
}

float Image::getHeight() const
{
	return rec.getLength().getY();
}

float Image::getX() const
{
	return rec.getCenter().getX();
}

float Image::getY() const
{
	return rec.getCenter().getY();
}

Vector3D Image::getLeftPos() const
{
	return rec.getLeft();
}

void Image::setFrames(int start, int end)
{
	startFrame = start;
	endFrame = end;
}

float Image::getRadians() const
{
	return rec.getAngle();
}

float Image::getRadians(const Vector3D& vec) const
{
	return rec.getAngle(vec);
}

float Image::getDegrees() const
{
	return (float) ((rec.getAngle()*180)/PI);
}

float Image::getDegrees(const Vector3D& vec) const
{
	return (float) ((rec.getAngle(vec)*180)/PI);
}

int Image::getCurrentFrame() const
{
	return currentFrame;
}

const sRectangle* Image::getSpriteDataRect() const
{
	return spriteData->rect;
}

const SDL_Color& Image::getColorFilter() const
{
	return colorFilter;
}

SpriteData* Image::getSpriteData()
{
	return spriteData;
}

const bool Image::getFlipV() const
{
	return spriteData->flipV;
}

const bool Image::getFlipH() const
{
	return spriteData->flipH;
}

Graphics* Image::getGraphics() const
{
	return graphics;
}

float Image::getScale() const
{
	return rec.getScale();
}

bool Image::getIsInitialized()
{
	return isInitialized;
}

std::string Image::getTextureName() const
{
	return spriteData->textureName;
}

float Image::getRecWidth() const
{
	return rec.getWidth();
}

float Image::getSpriteDataWidth() const
{
	return spriteData->rect->getWidth();
}


///////////////////
//		Set      //
///////////////////
void Image::set(Image& image)
{
	SpriteData* l_spriteData = image.getSpriteData();
	initialize(image.getGraphics(), (int) l_spriteData->rect->getWidth(), (int) l_spriteData->rect->getHeight(), image.getCols(), l_spriteData->texture, image.getTextureName());
	isDisplayingRec = image.getIsRectDisplaying();
	setCurrentFrame(image.getCurrentFrame());
	rec.set(image.getRectangle());
	visible = image.getVisible();
}
void Image::setCols(int cols)
{
	this->cols = cols;
}

void Image::setIsDisplayingRec(bool isDisplayingRec)
{
	this->isDisplayingRec = isDisplayingRec;
}

void Image::setX(float x)
{
	translateX(x-getX());
}

void Image::setY(float y)
{
	translateY(y-getY());
}

void Image::setPos(const Vector3D& center)
{
	Vector3D translateV(getPos(), center);
	translate(translateV);
}

void Image::setLeftPos(const Vector3D& left)
{
	Vector3D translateV(getLeftPos(), left);
	translate(translateV);
}

void Image::setDegrees(float degrees)
{
	setRadians((float) ((degrees*PI)/180), Vector3D(1.0f,0.0f));
}

void Image::setDegrees(float degrees, const Vector3D& vec)
{
	setRadians((float) ((degrees*PI)/180), vec);
}

void Image::setRadians(float radians, const Vector3D& vec)
{
	float angle = radians - rec.getAngle(vec);
	rotateRadians(angle, getPos());
}

void Image::setRadians(float radians)
{
	setRadians(radians, Vector3D(1.0f,0.0f));
}

void Image::setScale(float scale, const Vector3D& center)
{

}

void Image::setDegrees(float degrees, const Vector3D& vec,
		const Vector3D& center)
{
}

void Image::setRadians(float radians, const Vector3D& vec,
		const Vector3D& center)
{
}

void Image::setPositionX(float x, const Vector3D& vec)
{
}

void Image::setPositionY(float y, const Vector3D& vec)
{
}

void Image::setPosition(const Vector3D& p)
{
}

void Image::setPositionX(float x)
{
}

void Image::setPositionY(float y)
{
}

void Image::setFlipH(bool b, const Vector3D& center)
{

}

void Image::setFlipV(bool b, const Vector3D& center)
{
}


void Image::setSpriteDataRect(sRectangle* rect)
{
	spriteData->rect = rect;
}

void Image::setColorFilter(SDL_Color& colorFilter)
{
	this->colorFilter = colorFilter;
}

void Image::setFlipH(bool flipHorizontal)
{
	if(spriteData->flipH != flipHorizontal)
	{
		rec.flipHF(getPos());
	}
	spriteData->flipH = flipHorizontal;
}

void Image::setFlipV(bool flipVertical)
{
	if(spriteData->flipV != flipVertical)
	{
		rec.flipVF(getPos());
	}
	spriteData->flipV = flipVertical;
}

void Image::setScale(float scale)
{
	float factor = scale*(1.0f/getScale());
	this->scale(factor, getPos());
}

void Image::setGraphics(Graphics* g)
{
	graphics = g;
}

void Image::setSize(int size)
{
	setScale((size)/getSpriteDataWidth());
}

void Image::setSpriteData(const SpriteData& spriteData)
{
	this->spriteData->flipH = spriteData.flipH;
	this->spriteData->flipV = spriteData.flipV;

	this->spriteData->texture = spriteData.texture;
	this->spriteData->textureName = spriteData.textureName;

	this->spriteData->rect->set((*spriteData.rect));
}

void Image::setRec(const Rectangle& rec)
{
	this->rec.set(rec);
}

void Image::setRec(const Form& rec)
{
	this->rec.set(rec);
}

void Image::clearTexture()
{
	this->spriteData->texture = NULL;
}

void Image::loadTexture()
{
	// this->spriteData->texture = FileManager::getInstance().getDefTexture(spriteData->textureName);
}

void Image::initialize(Graphics* graphics, int width, int height, int cols,
		SDL_Texture* texture, std::string textureName)
{
	this->graphics = graphics;
	spriteData->texture = texture;
	if(cols == 0)
		this->cols = 1;
	else
		this->cols = cols;
	spriteData->rect->setLeft((currentFrame % this->cols)*width,
			(currentFrame / this->cols)*height,
			width,
			height);
	this->rec.set(Vector3D(width*0.5f,  height*0.5f), Vector3D(width, height), 0);
	spriteData->textureName = textureName;
	isInitialized = true;
}

void Image::draw()
{
	draw(graphics);
}

void Image::draw(Graphics* g)
{
	// (g) && (spriteData->texture) &&
	if(g && spriteData->texture && visible >= 0.01f)
	{
		/*
		Graphics2D g2d = (Graphics2D)g;
		AffineTransform old = g2d.getTransform();

		g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, visible));

		g2d.translate(rec.getCenter().x + (int) (rec.getLength().x)*((spriteData.flipH)?0:0),
				rec.getCenter().y + (int) (rec.getLength().y)*((spriteData.flipV)?0:0));

		g2d.scale(rec.getLength().x/spriteData.rect.getWidth(), rec.getLength().y/spriteData.rect.getHeight());

		float rot = (float) (-rec.getAngle() + ((spriteData.flipH)?Math.PI:0));
		if(Math.abs(rot) > 0.001 && Math.abs(rot - Math.PI*2) > 0.001)
			g2d.rotate(rot, 0,  0);

		g2d.translate(-spriteData.rect.getWidth()*(0.5 - ((spriteData.flipH)?1:0)), -spriteData.rect.getHeight()*(0.5 - ((spriteData.flipV)?1:0)));

		g2d.drawImage(spriteData.texture,
				0,
				0,
				(int) (spriteData.rect.getWidth())*((spriteData.flipH)?-1:1),
				(int) (spriteData.rect.getHeight())*((spriteData.flipV)?-1:1),
				(int) (spriteData.rect.getX()),
				(int) (spriteData.rect.getY()),
				(int) (spriteData.rect.getX() + spriteData.rect.getWidth()),
				(int) (spriteData.rect.getY() + spriteData.rect.getHeight()),
				null, null);
		g2d.setTransform(old);

		if(isDisplayingRec)
		{
			g2d.setColor(Color.CYAN);
			Polygon pol = this.rec.getPolygon();
			g2d.drawPolygon(pol);
		}
		g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 1));*/
	}
}

void Image::draw(const Vector3D& translation)
{
	draw(graphics, translation);
}

void Image::draw(Graphics* g, const Vector3D& translation)
{
	if(g && spriteData->texture && visible >= 0.01f)
	{

	}
}

void Image::draw(Graphics* g, const Vector3D& translation, float scale)
{
	if(g && spriteData->texture && visible >= 0.01f)
	{

	}
}

void Image::setCurrentFrame(int current)
{
	if(current > 0)
	{
		currentFrame = current;
		setRect();
	}
}

bool Image::hasAlpha()
{
	/*
	try
	{
		PixelGrabber pg = new PixelGrabber(spriteData.texture, 0, 0, 1, 1, false);
		pg.grabPixels();

		return pg.getColorModel().hasAlpha();
	}
	catch (InterruptedException e)
	{
		return false;
	}*/

	assert(false);
	return false;
}

void Image::setRect()
{
	spriteData->rect->setLeft((currentFrame % cols)*spriteData->rect->getWidth(),
					(currentFrame / cols)*spriteData->rect->getHeight(),
					spriteData->rect->getWidth(),
					spriteData->rect->getHeight());
}


///////////////////////////////
//		Transformations      //
///////////////////////////////
void Image::translate(const Vector3D& vec)
{
	rec.translate(vec);
}

void Image::translateX(float vecX)
{
	rec.translateX(vecX);
}

void Image::translateY(float vecY)
{
	rec.translateY(vecY);
}

void Image::flipH(const Vector3D& center)
{
	rec.flipHF(center);
	spriteData->flipH = !spriteData->flipH;
}

void Image::flipV(const Vector3D& center)
{
	rec.flipVF(center);
	spriteData->flipV = !spriteData->flipV;
}

void Image::scale(float factor, const Vector3D& center)
{
	if(factor)
		rec.scaleF(factor, center);
	else
		rec.scaleF(0.0001f, center);
}

void Image::rotateRadians(float radians, const Vector3D& center)
{
	rec.rotateRadians(radians, center);
}

void Image::setVisible(float f)
{
	visible *= f;
	if(visible > 1.0f)
		visible = 1.0f;
	else if(visible < 0.01f)
		visible = 0.005f;
}

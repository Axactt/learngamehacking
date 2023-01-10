#include<string>
struct Point2D
{
	int x;
	int y;
};
class Box// Mixin box class intended to be mixed in(inherited from) other class instaed of being instantiated on its own, to add properties to a class
{
private:
	Point2D m_topLeft {};
	Point2D m_bottomRight {};
public:
	void setTopLeft(Point2D point)
	{
		m_topLeft = point;
	}
	void setBottomRight(Point2D point)
	{
		m_bottomRight = point;
	}
};
class Label // mixin Label class
	// note no custom constructor in both mixin class
{
private:
	std::string m_text {};
	int m_fontSize {};
public:
	void setText(const std::string_view str)
	{
		m_text = str;
	}
	void setFontSize(int fontSize)
	{
		m_fontSize = fontSize;
	}
};

class Button: public Box, public Label
{
	// Nothing in body of button class
};

int main()
{
	Button button {};
	button.Box::setTopLeft({ 1,1 });
	button.Box::setBottomRight({ 10,10 });
	button.Label::setText("Username:");
	button.Label::setFontSize(6);
	return 0;
}
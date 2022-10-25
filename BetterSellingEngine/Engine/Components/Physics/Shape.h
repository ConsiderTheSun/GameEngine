#pragma once

class Shape {
public:
	enum ShapeType{Default, OBB, OBC, OBC2AA};
	
	ShapeType GetShapeType() { return shapeType; }
protected:
	ShapeType shapeType = Default;
};
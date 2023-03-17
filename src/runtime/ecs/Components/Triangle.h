#pragma once
//实体类 包括一个Transform组件 和顶点数据
	class  Triangle
	{
		
	public:
		Triangle();
		~Triangle();
	
		//std::array<Vertex, 3>vertices;

		//指定棱锥的四个顶点
		float vertex[4][3] = {
			{0, 0, 0},
			{0.2, 0.2, 0},
			{-0.3, 0, 0},
			{0, -0.3, 0}
		};


		void Draw();
	};
	

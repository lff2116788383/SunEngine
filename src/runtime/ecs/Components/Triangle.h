#pragma once
//ʵ���� ����һ��Transform��� �Ͷ�������
	class  Triangle
	{
		
	public:
		Triangle();
		~Triangle();
	
		//std::array<Vertex, 3>vertices;

		//ָ����׶���ĸ�����
		float vertex[4][3] = {
			{0, 0, 0},
			{0.2, 0.2, 0},
			{-0.3, 0, 0},
			{0, -0.3, 0}
		};


		void Draw();
	};
	

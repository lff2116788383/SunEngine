#pragma once

#include "singleton/Singleton.h"

	class  VukanRenderer 
	{
		DECL_SINGLETON(VukanRenderer)
	public:
		void DrawFrame();
		void Renderer();
	private:

	};


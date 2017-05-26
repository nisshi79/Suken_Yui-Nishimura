#pragma once

#include "../sukenlib/GameEngine/Object/Object.h"
#include "../sukenlib/GameEngine/Input.h"
#include "../sukenlib/Utility/Graph.h"
#include <functional>

namespace suken {
	/**
	*	@brief 画像を使って、四角いボタンを作成します
	*/
	class COButtonSquare :public CObject{
	public:
		/**
		*	@brief コンストラクタ　第六引数はラムダ式で指定
		*/
		COButtonSquare(Graph graph, int x1, int y1, int x2, int y2, std::function<void()> func):graph(graph),x1(x1),y1(y1),x2(x2),y2(y2),func(func){}

		/**
		*	@brief コンストラクタ　第四引数はラムダ式で指定
		*/
		COButtonSquare(Graph graph, int x, int y, std::function<void()> func) :graph(graph), x1(x), y1(y), func(func) {
			std::pair<int,int> buf = graph.GetSize();
			x2 = x1 + buf.first;
			y2 = y1 + buf.second;
		}
	private:

		void Loop()override {
			if (Input.GetMouseExit(Input.mouse.L, x1, y1, x2, y2)) {
				func();
			}
		}

		void Draw()override {
			graph.DrawExtend(x1, y1, x2, y2);
			if (Input.GetMouseDown(Input.mouse.L,x1, y1, x2, y2)) {
				DrawMode* buf = GetScene()->GetDrawMode();
				if (buf != nullptr) {
					DxLib::SetDrawBlendMode(DX_BLENDMODE_ADD, buf->param*0.3);
				}
				else {
					DxLib::SetDrawBlendMode(DX_BLENDMODE_ADD, 75);
				}
				DxLib::DrawBox(x1, y1, x2, y2, WHITE, true);
				if (buf != nullptr) {
					DxLib::SetDrawBlendMode(buf->blendMode, buf->param);
				}
				else {
					DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);
				}
			}
		}

		Graph graph;
		int x1;
		int y1;
		int x2;
		int y2;
		std::function<void()> func;

		OBJECT_CHARM(COButtonSquare)
	};
}
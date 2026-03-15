#pragma once

#include "eldrun/runtime/app_state.hpp"

namespace eldrun::editor
{
	class EditorAppState final : public eldrun::runtime::IAppState
	{
	public:
		void on_enter() override;
		void on_exit() override;
		void update(eldrun::core::Timestep delta_time) override;
		void render(eldrun::runtime::IFrameContext& frame) override;
	private:
		double m_elapsed_time { 0.0 };
	};
}
#pragma once

namespace ZeroGUI
{
	namespace Input
	{
		bool mouseDown[5];
		bool mouseDownAlready[256];

		bool keysDown[256];
		bool keysDownAlready[256];

		bool IsAnyMouseDown()
		{
			if (mouseDown[0]) return true;
			if (mouseDown[1]) return true;
			if (mouseDown[2]) return true;
			if (mouseDown[3]) return true;
			if (mouseDown[4]) return true;

			return false;
		}

		bool IsMouseClicked(int button, int element_id, bool repeat)
		{
			if (mouseDown[button])
			{
				if (!mouseDownAlready[element_id])
				{
					mouseDownAlready[element_id] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				mouseDownAlready[element_id] = false;
			}
			return false;
		}
		bool IsKeyPressed(int key, bool repeat)
		{
			if (keysDown[key])
			{
				if (!keysDownAlready[key])
				{
					keysDownAlready[key] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				keysDownAlready[key] = false;
			}
			return false;
		}

		void Handle()
		{
			if (IFH(GetAsyncKeyState)(0x01))
				mouseDown[0] = true;
			else
				mouseDown[0] = false;
		}
	}
}

namespace ZeroGUI
{
	namespace Colors
	{
		flinearcolor Text = { 1.0f, 1.0f, 1.0f, 1.0f };
		flinearcolor Text_Shadow = { 0.0f, 0.0f, 0.0f, 0.0f };
		flinearcolor Text_Outline = { 0.0f, 0.0f, 0.0f, 0.30f };

		flinearcolor Window_Background = { 0.15f, 0.15f, 0.15f, 1.0f };
		flinearcolor Window_Header = { 0.5f, 0.0f, 0.0f, 1.0f };

		flinearcolor Button_Idle = { 0.5f, 0.0f, 0.0f, 1.0f };    // Dark red
		flinearcolor Button_Hovered = { 0.55f, 0.0f, 0.0f, 1.0f };  // Slightly brighter red when hovered
		flinearcolor Button_Active = { 0.6f, 0.0f, 0.0f, 1.0f };   // Even brighter red when active

		flinearcolor Checkbox_Idle = { 0.10f, 0.10f, 0.10f, 1.0f };
		flinearcolor Checkbox_Hovered = { 0.15f, 0.15f, 0.15f, 1.0f };
		flinearcolor Checkbox_Enabled = { 0.5f, 0.0f, 0.0f, 1.0f };

		flinearcolor Combobox_Idle = { 0.10f, 0.10f, 0.10f, 1.0f };
		flinearcolor Combobox_Hovered = { 0.15f, 0.15f, 0.15f, 1.0f };
		flinearcolor Combobox_Elements = { 0.42f, 0.80f, 0.98f, 1.0f };

		flinearcolor Slider_Idle = { 0.10f, 0.10f, 0.10f, 1.0f };
		flinearcolor Slider_Hovered = { 0.15f, 0.15f, 0.15f, 1.0f };
		flinearcolor Slider_Progress = { 0.5f, 0.0f, 0.0f, 1.0f };
		flinearcolor Slider_Button = { 0.50f, 0.10f, 0.00f, 1.0f }; // 0.22f, 0.45f, 0.78f

		flinearcolor ColorPicker_Background = { 0.05f, 0.05f, 0.05f, 1.0f };

		flinearcolor LightPurple = { 0.80f, 0.60f, 0.90f, 1.0f };
		flinearcolor LightPurple_Hovered = { 0.85f, 0.70f, 0.95f, 1.0f };
	}

	namespace PostRenderer
	{
		struct DrawList
		{
			int type = -1; //1 = FilledRect, 2 = TextLeft, 3 = TextCenter, 4 = Draw_Line
			fvector2d pos;
			fvector2d size;
			flinearcolor color;
			const char* name;
			bool outline;

			fvector2d from;
			fvector2d to;
			int thickness;
		};
		DrawList drawlist[128];

		void drawFilledRect(fvector2d pos, float w, float h, flinearcolor color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 1;
					drawlist[i].pos = pos;
					drawlist[i].size = fvector2d{ w, h };
					drawlist[i].color = color;
					return;
				}
			}
		}
		void TextLeft(const char* name, fvector2d pos, flinearcolor color, bool outline)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 2;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}
		void TextCenter(const char* name, fvector2d pos, flinearcolor color, bool outline)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 3;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}
		void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 4;
					drawlist[i].from = from;
					drawlist[i].to = to;
					drawlist[i].thickness = thickness;
					drawlist[i].color = color;
					return;
				}
			}
		}
	}

	ucanvas* canvas;
	wchar_t* s2wc(const char* c)
	{
		const size_t cSize = IFH(strlen)(c) + 1;
		wchar_t* wc = new wchar_t[cSize];
		IFH(mbstowcs)(wc, c, cSize);

		return wc;
	}

	bool hover_element = false;
	fvector2d menu_pos = fvector2d{ 0, 0 };
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	fvector2d first_element_pos = fvector2d{ 0, 0 };

	fvector2d last_element_pos = fvector2d{ 0, 0 };
	fvector2d last_element_size = fvector2d{ 0, 0 };

	int current_element = -1;
	fvector2d current_element_pos = fvector2d{ 0, 0 };
	fvector2d current_element_size = fvector2d{ 0, 0 };
	int elements_count = 0;

	bool sameLine = false;

	bool pushY = false;
	float pushYvalue = 0.0f;

	void SetupCanvas(ucanvas* _canvas)
	{
		canvas = _canvas;
	}

	fvector2d CursorPos()
	{
		POINT cursorPos;
		IFH(GetCursorPos)(&cursorPos);
		return fvector2d{ (float)cursorPos.x, (float)cursorPos.y };
	}
	bool MouseInZone(fvector2d pos, fvector2d size)
	{
		fvector2d cursor_pos = CursorPos();

		if (cursor_pos.x > pos.x && cursor_pos.y > pos.y)
			if (cursor_pos.x < pos.x + size.x && cursor_pos.y < pos.y + size.y)
				return true;

		return false;
	}

	void Draw_Cursor(bool toggle)
	{
		if (toggle)
		{
			fvector2d cursorPos = CursorPos();
			flinearcolor cursorColor{ 0.5f, 0.00f, 0.00f, 1.0f };
			int cursorSize = 20;

			canvas->k2_draw_line(cursorPos, cursorPos + fvector2d{ 35.0f, 10.0f }, 1, cursorColor);

			for (int i = 1; i <= cursorSize; i++)
			{
				float progress = static_cast<float>(i) / cursorSize;
				fvector2d lineEnd = cursorPos + fvector2d{ 35.0f * progress, 10.0f * progress };

				canvas->k2_draw_line(cursorPos, lineEnd, 1, cursorColor);
			}

			canvas->k2_draw_line(cursorPos, cursorPos + fvector2d{ 15.0f, 30.0f }, 1, cursorColor);
			canvas->k2_draw_line(cursorPos + fvector2d{ 35.0f, 10.0f }, cursorPos + fvector2d{ 15.0f, 30.0f }, 1, cursorColor);
		}
	}

	void SameLine()
	{
		sameLine = true;
	}
	void PushNextElementY(float y, bool from_last_element = true)
	{
		pushY = true;
		if (from_last_element)
			pushYvalue = last_element_pos.y + last_element_size.y + y;
		else
			pushYvalue = y;
	}
	void NextColumn(float x)
	{
		offset_x = x;
		PushNextElementY(first_element_pos.y, false);
	}
	void ClearFirstPos()
	{
		first_element_pos = fvector2d{ 0, 0 };
	}

	void TextLeft(const char* name, fvector2d pos, flinearcolor color, bool outline)
	{
		int length = IFH(strlen)(name) + 1;
		canvas->k2_draw_text(render::font, fstring{ s2wc(name) }, pos, fvector2d{ 0.97f, 0.97f }, color, false, Colors::Text_Shadow, fvector2d{ pos.x + 1, pos.y + 1 }, false, true, true, Colors::Text_Outline);
	}
	void TextCenter(const char* name, fvector2d pos, flinearcolor color, bool outline)
	{
		int length = IFH(strlen)(name) + 1;
		canvas->k2_draw_text(render::font, fstring{ s2wc(name) }, pos, fvector2d{ 0.97f, 0.97f }, color, false, Colors::Text_Shadow, fvector2d{ pos.x + 1, pos.y + 1 }, true, true, true, Colors::Text_Outline);
	}



	void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
	{
		canvas->k2_draw_line(fvector2d{ from.x, from.y }, fvector2d{ to.x, to.y }, thickness, color);
	}
	void drawFilledRect(fvector2d initial_pos, float w, float h, flinearcolor color)
	{
		for (float i = 0.0f; i < h; i += 1.0f)
			canvas->k2_draw_line(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, 1.0f, color);
	}
	void drawFilledRect_trans(fvector2d initial_pos, float w, float h, flinearcolor color)
	{
		for (float i = 0.0f; i < h; i += 1.0f)
			canvas->k2_draw_line(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, 0.4f, color);
	}
	void DrawFilledCircle(fvector2d pos, float r, flinearcolor color)
	{
		float smooth = 0.07f;

		double PI = 3.14159265359;
		int size = (int)(2.0f * PI / smooth) + 1;

		float angle = 0.0f;
		int i = 0;

		for (; angle < 2 * PI; angle += smooth, i++)
		{
			Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x + cosf(angle) * r, pos.y + sinf(angle) * r }, 1.0f, color);
		}
	}
	void DrawCircle(fvector2d pos, int radius, int numSides, flinearcolor Color)
	{
		float PI = 3.1415927f;

		float Step = PI * 2.0 / numSides;
		int Count = 0;
		fvector2d V[128];
		for (float a = 0; a < PI * 2.0; a += Step) {
			float X1 = radius * defines::math->cos(a) + pos.x;
			float Y1 = radius * defines::math->sin(a) + pos.y;
			float X2 = radius * defines::math->cos(a + Step) + pos.x;
			float Y2 = radius * defines::math->sin(a + Step) + pos.y;
			V[Count].x = X1;
			V[Count].y = Y1;
			V[Count + 1].x = X2;
			V[Count + 1].y = Y2;
			//Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ X2, Y2 }, 1.0f, Color); // Points from Centre to ends of circle
			Draw_Line(fvector2d{ V[Count].x, V[Count].y }, fvector2d{ X2, Y2 }, 1.0f, Color);// Circle Around
		}
	}

	fvector2d dragPos;
	bool Window(const char* name, fvector2d* pos, fvector2d size, bool isOpen, float width, float height)
	{
		elements_count = 0;

		if (!isOpen)
			return false;

		bool isHovered = MouseInZone(fvector2d{ pos->x, pos->y }, size);

		//Drop last element
		if (current_element != -1 && !IFH(GetAsyncKeyState)(0x1))
		{
			current_element = -1;
		}

		//Drag
		if (hover_element && IFH(GetAsyncKeyState)(0x1))
		{

		}
		else if ((isHovered || dragPos.x != 0) && !hover_element)
		{
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				fvector2d cursorPos = CursorPos();

				cursorPos.x -= size.x;
				cursorPos.y -= size.y;

				if (dragPos.x == 0)
				{
					dragPos.x = (cursorPos.x - pos->x);
					dragPos.y = (cursorPos.y - pos->y);
				}
				pos->x = cursorPos.x - dragPos.x;
				pos->y = cursorPos.y - dragPos.y;
			}
			else
			{
				dragPos = fvector2d{ 0, 0 };
			}
		}
		else
		{
			hover_element = false;
		}


		offset_x = 0.0f; offset_y = 0.0f;
		menu_pos = fvector2d{ pos->x, pos->y };
		first_element_pos = fvector2d{ 0, 0 };
		current_element_pos = fvector2d{ 0, 0 };
		current_element_size = fvector2d{ 0, 0 };

		// Dark transparent background
		//drawFilledRect_trans(fvector2d{ 0, 0 }, width, height, flinearcolor{ 0.0f, 0.0f, 0.0f, 0.4f });


		// Bg
		drawFilledRect(fvector2d{ pos->x, pos->y }, size.x, size.y, Colors::Window_Background);
		//drawFilledRect(fvector2d{ pos->x, pos->y }, 122, size.y, flinearcolor{ 0.006f, 0.006f, 0.006f, 1.0f });//My tabs bg

		// Header
		drawFilledRect(fvector2d{ pos->x, pos->y }, size.x, 25.0f, Colors::Window_Header);

		offset_y += 25.0f;

		// Title
		fvector2d titlePos = fvector2d{ pos->x + size.x / 2, pos->y + 25 / 2 };
		TextCenter(name, titlePos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

		return true;
	}

	void Text(const char* text, bool center = false, bool outline = false)
	{
		elements_count++;

		float size = 25;
		fvector2d padding = fvector2d{ 10, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		if (!sameLine)
			offset_y += size + padding.y;

		//Text
		fvector2d textPos = fvector2d{ pos.x + 5.0f, pos.y + size / 2 };
		if (center)
			TextCenter(text, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);
		else
			TextLeft(text, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);

		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}



	bool ButtonTab(const char* name, fvector2d size, bool active)
	{
		elements_count++;

		fvector2d padding = { 5, 10 };
		fvector2d pos = { menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}

		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		bool isHovered = MouseInZone(pos, size);

		// Background
		flinearcolor buttonColor = active ? Colors::Button_Active : (isHovered ? Colors::Button_Hovered : Colors::Button_Idle);
		drawFilledRect(pos, size.x, size.y, buttonColor);

		if (!sameLine)
			offset_y += size.y + padding.y;

		// Text
		fvector2d textPos = { pos.x + size.x / 2, pos.y + size.y / 2 };
		TextCenter(name, textPos, { 1.0f, 1.0f, 1.0f, 1.0f }, false);

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			return true;

		return false;
	}

	bool Button(const char* name, fvector2d size)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 5, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

		//Bg
		if (isHovered)
		{
			drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Colors::Button_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Colors::Button_Idle);
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Text
		fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
		//if (!TextOverlapedFromActiveElement(textPos))
		TextCenter(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			return true;

		return false;
	}
	void Checkbox(const char* name, bool* value)
	{
		elements_count++;

		float size = 18;
		fvector2d padding = fvector2d{ 10, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, fvector2d{ size, size });

		//Bg
		if (isHovered)
		{
			drawFilledRect(fvector2d{ pos.x, pos.y }, size, size, Colors::Checkbox_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(fvector2d{ pos.x, pos.y }, size, size, Colors::Checkbox_Idle);
		}

		if (!sameLine)
			offset_y += size + padding.y;

		if (*value)
		{
			drawFilledRect(fvector2d{ pos.x + 3, pos.y + 3 }, size - 6, size - 6, Colors::Checkbox_Enabled);
			//drawFilledRect(fvector2d{ pos.x + 9, pos.y + 9 }, size - 18, size - 18, Colors::Checkbox_Hovered);
		}



		//Text
		fvector2d textPos = fvector2d{ pos.x + size + 5.0f, pos.y + size / 2 };
		//if (!TextOverlapedFromActiveElement(textPos))
		TextLeft(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);


		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			*value = !*value;
	}
	//void SliderInt( const char* name, int* value, int min, int max )
	//{
	//	elements_count++;

	//	fvector2d size = fvector2d { 240, 50 };
	//	fvector2d slider_size = fvector2d { 200, 10 };
	//	fvector2d padding = fvector2d { 10, 15 };
	//	fvector2d pos = fvector2d { menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
	//	if ( sameLine )
	//	{
	//		pos.x = last_element_pos.x + last_element_size.x + padding.x;
	//		pos.y = last_element_pos.y;
	//	}
	//	if ( pushY )
	//	{
	//		pos.y = pushYvalue;
	//		pushY = false;
	//		pushYvalue = 0.0f;
	//		offset_y = pos.y - menu_pos.y;
	//	}
	//	bool isHovered = MouseInZone( fvector2d { pos.x, pos.y + slider_size.y + padding.y }, slider_size );

	//	if ( !sameLine )
	//		offset_y += size.y + padding.y;

	//	//Bg
	//	if ( isHovered || current_element == elements_count )
	//	{
	//		//Drag
	//		if ( Input::IsMouseClicked( 0, elements_count, true ) )
	//		{
	//			current_element = elements_count;

	//			fvector2d cursorPos = CursorPos( );
	//			*value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
	//			if ( *value < min ) *value = min;
	//			if ( *value > max ) *value = max;
	//		}

	//		drawFilledRect( fvector2d { pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Hovered );
	//		drawFilledRect( fvector2d { pos.x, pos.y + slider_size.y + padding.y + 5.0f }, 5.0f, 5.0f, Colors::Slider_Progress );

	//		hover_element = true;
	//	}
	//	else
	//	{
	//		drawFilledRect( fvector2d { pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Idle );
	//		drawFilledRect( fvector2d { pos.x, pos.y + slider_size.y + padding.y + 5.0f }, 5.0f, 5.0f, Colors::Slider_Progress );
	//	}


	//	//Value
	//	float oneP = slider_size.x / (max - min);
	//	drawFilledRect( fvector2d { pos.x, pos.y + slider_size.y + padding.y }, oneP * (*value - min), slider_size.y, Colors::Slider_Progress );
	//	//drawFilledRect(fvector2d{ pos.x + oneP * (*value - min) - 10.0f, pos.y + slider_size.y - 5.0f + padding.y }, 20.0f, 20.0f, Colors::Slider_Button);
	//	DrawFilledCircle( fvector2d { pos.x + oneP * (*value - min), pos.y + slider_size.y + 3.3f + padding.y }, 10.0f, Colors::Slider_Button );
	//	DrawFilledCircle( fvector2d { pos.x + oneP * (*value - min), pos.y + slider_size.y + 3.3f + padding.y }, 5.0f, Colors::Slider_Progress );

	//	char buffer [ 32 ];
	//	sprintf_s( buffer, "%i", *value );
	//	fvector2d valuePos = fvector2d { pos.x + oneP * (*value - min), pos.y + slider_size.y + 25 + padding.y };
	//	TextCenter( buffer, valuePos, flinearcolor { 1.0f, 1.0f, 1.0f, 1.0f }, false );

	//	//Text
	//	fvector2d textPos = fvector2d { pos.x + 5, pos.y + 10 };
	//	TextLeft( name, textPos, flinearcolor { 1.0f, 1.0f, 1.0f, 1.0f }, false );


	//	sameLine = false;
	//	last_element_pos = pos;
	//	last_element_size = size;
	//	if ( first_element_pos.x == 0.0f )
	//		first_element_pos = pos;
	//}
	void SliderFloat(const char* name, float* value, float min, float max, const char* format = "%.0f")
	{
		elements_count++;

		fvector2d size = { 210, 40 };
		fvector2d slider_size = { 170, 7 };
		fvector2d adjust_zone = { 0, 20 };
		fvector2d padding = { 10, 15 };
		fvector2d pos = { menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}

		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		bool isHovered = MouseInZone(pos, { slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

		if (!sameLine)
			offset_y += size.y + padding.y;

		// Background
		flinearcolor sliderIdleColor = isHovered || current_element == elements_count ? Colors::Slider_Hovered : Colors::Slider_Idle;
		drawFilledRect({ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, sliderIdleColor);
		DrawFilledCircle({ pos.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Progress);
		DrawFilledCircle({ pos.x + slider_size.x, pos.y + padding.y + 9.3f }, 3.1f, sliderIdleColor);

		if (isHovered || current_element == elements_count)
		{
			// Drag
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				current_element = elements_count;

				fvector2d cursorPos = CursorPos();
				*value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
				if (*value < min)
					*value = min;
				if (*value > max)
					*value = max;
			}

			hover_element = true;
		}

		// Text
		fvector2d textPos = { pos.x, pos.y + 5 };
		TextLeft(name, textPos, Colors::Text, false);

		// Value
		float oneP = slider_size.x / (max - min);
		drawFilledRect({ pos.x, pos.y + slider_size.y + padding.y }, oneP * (*value - min), slider_size.y, Colors::Slider_Progress);
		DrawFilledCircle({ pos.x + oneP * (*value - min), pos.y + slider_size.y + 2.66f + padding.y }, 8.0f, Colors::Slider_Button);
		DrawFilledCircle({ pos.x + oneP * (*value - min), pos.y + slider_size.y + 2.66f + padding.y }, 4.0f, Colors::Slider_Progress);

		char buffer[32];
		sprintf_s(buffer, format, *value);
		fvector2d valuePos = { pos.x + oneP * (*value - min), pos.y + slider_size.y + 20 + padding.y };
		TextCenter(buffer, valuePos, Colors::Text, false);

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}



	bool checkbox_enabled[256];
	void Combobox(const char* name, fvector2d size, int* value, const char* arg, ...)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 5, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

		//Bg
		if (isHovered || checkbox_enabled[elements_count])
		{
			drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Colors::Combobox_Hovered);

			hover_element = true;
		}
		else
		{
			drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Colors::Combobox_Idle);
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Text
		fvector2d textPos = fvector2d{ pos.x + size.x + 5.0f, pos.y + size.y / 2 };
		TextLeft(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

		//Elements
		bool isHovered2 = false;
		fvector2d element_pos = pos;
		int num = 0;

		if (checkbox_enabled[elements_count])
		{
			current_element_size.x = element_pos.x - 5.0f;
			current_element_size.y = element_pos.y - 5.0f;
		}
		va_list arguments;
		for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const char*))
		{
			//Selected Element
			if (num == *value)
			{
				fvector2d _textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
				TextCenter((char*)arg, _textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
			}

			if (checkbox_enabled[elements_count])
			{
				element_pos.y += 25.0f;

				isHovered2 = MouseInZone(fvector2d{ element_pos.x, element_pos.y }, fvector2d{ size.x, 25.0f });
				if (isHovered2)
				{
					hover_element = true;
					PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 25.0f, Colors::Combobox_Hovered);

					//Click
					if (Input::IsMouseClicked(0, elements_count, false))
					{
						*value = num;
						checkbox_enabled[elements_count] = false;
					}
				}
				else
				{
					PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 25.0f, Colors::Combobox_Idle);
				}

				PostRenderer::TextLeft((char*)arg, fvector2d{ element_pos.x + 5.0f, element_pos.y + 15.0f }, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
			}
			num++;
		}
		va_end(arguments);
		if (checkbox_enabled[elements_count])
		{
			current_element_size.x = element_pos.x + 5.0f;
			current_element_size.y = element_pos.y + 5.0f;
		}


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
		{
			checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];
		}
		if (!isHovered && !isHovered2 && Input::IsMouseClicked(0, elements_count, false))
		{
			checkbox_enabled[elements_count] = false;
		}
	}

	int active_hotkey = -1;
	bool already_pressed = false;
	std::string VirtualKeyCodeToString(UCHAR virtualKey)
	{
		UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

		if (virtualKey == VK_LBUTTON)
		{
			return ("Left Mouse Button");
		}
		if (virtualKey == VK_RBUTTON)
		{
			return ("Right Mouse Button");
		}
		if (virtualKey == VK_MBUTTON)
		{
			return ("Middle Mouse Button");
		}
		if (virtualKey == VK_XBUTTON1)
		{
			return ("Side Button 1");
		}
		if (virtualKey == VK_XBUTTON2)
		{
			return ("Side Button 2");
		}

		CHAR szName[128];
		int result = 0;
		switch (virtualKey)
		{
		case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
		case VK_RCONTROL: case VK_RMENU:
		case VK_LWIN: case VK_RWIN: case VK_APPS:
		case VK_PRIOR: case VK_NEXT:
		case VK_END: case VK_HOME:
		case VK_INSERT: case VK_DELETE:
		case VK_DIVIDE:
		case VK_NUMLOCK:
			scanCode |= KF_EXTENDED;
		default:
			result = IFH(GetKeyNameTextA)(scanCode << 16, szName, 128);
		}

		return szName;
	}
	void Hotkey(const char* name, fvector2d size, int* key)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 5, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y + (last_element_size.y / 2) - size.y / 2;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

		//Bg
		if (isHovered)
		{
			drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Colors::Button_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Colors::Button_Idle);
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		if (active_hotkey == elements_count)
		{
			//Text
			fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
			TextCenter("[Press Key]", textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

			if (!ZeroGUI::Input::IsAnyMouseDown())
			{
				already_pressed = false;
			}

			if (!already_pressed)
			{
				for (int code = 0; code < 255; code++)
				{
					if (IFH(GetAsyncKeyState)(code))
					{
						*key = code;
						active_hotkey = -1;
					}
				}
			}
		}
		else
		{
			//Text
			fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
			TextCenter((char*)VirtualKeyCodeToString(*key).c_str(), textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

			if (isHovered)
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					already_pressed = true;
					active_hotkey = elements_count;

					//Queue Fix
					for (int code = 0; code < 255; code++)
						if (IFH(GetAsyncKeyState)(code)) {}
				}
			}
			else
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					active_hotkey = -1;
				}
			}
		}


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	int active_picker = -1;
	flinearcolor saved_color;
	


	void Render()
	{
		for (int i = 0; i < 128; i++)
		{
			if (PostRenderer::drawlist[i].type != -1)
			{
				//Filled Rect
				if (PostRenderer::drawlist[i].type == 1)
				{
					ZeroGUI::drawFilledRect(PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].size.x, PostRenderer::drawlist[i].size.y, PostRenderer::drawlist[i].color);
				}
				//TextLeft
				else if (PostRenderer::drawlist[i].type == 2)
				{
					ZeroGUI::TextLeft(PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
				}
				//TextCenter
				else if (PostRenderer::drawlist[i].type == 3)
				{
					ZeroGUI::TextCenter(PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
				}
				//Draw_Line
				else if (PostRenderer::drawlist[i].type == 4)
				{
					Draw_Line(PostRenderer::drawlist[i].from, PostRenderer::drawlist[i].to, PostRenderer::drawlist[i].thickness, PostRenderer::drawlist[i].color);
				}

				PostRenderer::drawlist[i].type = -1;
			}
		}
	}
}



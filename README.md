1. Download Maps @ https://www.mediafire.com/file/rdl3bs5lc8jk1ym/mapcontent.rar/file 3/14/25
2. Place map images in mapcontent folder
   
3.If your using a fuser and need a solid black background do the follow:
should be in dmalib/includes/dmarender/renderwindow/renderwindow.cpp line 62ish
go to line 70 and add this
ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

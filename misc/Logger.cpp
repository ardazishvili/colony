#include "Logger.h"

void Logger::log()
{

  ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
  ImGui::Begin("Example: Log");
  if (ImGui::SmallButton("[Debug] Add 5 entries")) {
    static int counter = 0;
    for (int n = 0; n < 5; n++) {
      const char* categories[3] = { "info", "warn", "error" };
      const char* words[] = { "Bumfuzzled",    "Cattywampus",  "Snickersnee",
                              "Abibliophobia", "Absquatulate", "Nincompoop",
                              "Pauciloquent" };
      _log.AddLog(
        "[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
        ImGui::GetFrameCount(),
        categories[counter % IM_ARRAYSIZE(categories)],
        ImGui::GetTime(),
        words[counter % IM_ARRAYSIZE(words)]);
      counter++;
    }
  }
  ImGui::End();
  _log.Draw("Example: Log");
}

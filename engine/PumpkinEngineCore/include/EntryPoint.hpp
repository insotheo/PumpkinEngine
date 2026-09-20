#pragma once

extern Pumpkin::Application *CreatePumpkinApplication();

int main(int argc, char **agrv) {
  auto app = CreatePumpkinApplication();
  app->Run();
  delete app;
  return 0;
}

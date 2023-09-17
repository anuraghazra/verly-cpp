workspace "verly-cpp"
  architecture "x64"

  configurations
  {
    "Debug",
    "Release"
  }


project "verly"
  location "."
  kind "ConsoleApp"
  language "C++"

  targetdir ("bin/%{prj.name}")
  objdir ("bin-int/%{prj.name}")

  files
  {
    "src/**.hpp",
    "src/**.cpp"
  }

  includedirs
  {
    "./include",
  }

  filter "system:windows"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"

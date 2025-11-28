# LuckyNumberGenerator

LuckyNumberGenerator analyzes historical lottery data (Mega Millions and Powerball) to help you explore and generate “lucky” number sets. It computes simple, position-based frequencies and a quality score, then provides a lightweight GUI for interacting with the results.

This is a learning-driven, pragmatic C++17 project using Raylib for the UI and a small, testable architecture under the hood.

<img width="999" height="599" alt="image" src="https://github.com/user-attachments/assets/f1c34ccd-f882-4099-b16c-976f39df8a76" />
<img width="999" height="599" alt="image" src="https://github.com/user-attachments/assets/3bee86bb-556f-4840-80cd-0d57112d681b" />
<img width="999" height="599" alt="image" src="https://github.com/user-attachments/assets/adc5f7c9-3998-43c0-937c-2d863df34fe1" />

## Features

- Historical data parsing from CSV for Mega Millions and Powerball
- Position-based frequency analysis per draw slot (including Mega/Power balls)
- Per-number “quality” percentage and overall set average
- Generators for both games with validation of ranges and uniqueness
- GUI built with Raylib + raygui
- Scene-based UI with a `SceneManager` and dedicated scene classes
- Lock/unlock individual numbers and regenerate only the unlocked ones
- Automatic initial roll when entering a generator scene

## How It Works

- Data is loaded from CSV files in `Assets/Data/` via `FileManager`.
- `LuckyNumberGenerator` is an abstract base class that:
	- Stores draw history and exposes frequency/quality helpers
	- Provides `PrintLuckyNumbers()` and `GetOverallAverage()` convenience methods
- `PowerBallNumberGenerator` and `MegaMillionsNumberGenerator` derive from the base and implement `GetNumbers()`.
- `SceneManager` encapsulates scene state and app exit signaling.
- Each screen is implemented as its own scene class (`MainMenuScene`, `PowerBallScene`, `MegaMillionsScene`). Scenes render their contents and call back into `SceneManager` for navigation.

Quality metric: for a given set, the project computes position-based occurrence counts and derives simple percentages per position. The overall average is an aggregate (integer percentage) for quick comparison. This is not a predictor—just a way to explore historical tendencies.

## Project Structure

```
include/
	FileManager.hpp
	LuckyNumberGenerator.hpp
	MegaMillionsNumberGenerator.hpp
	PowerBallNumberGenerator.hpp
	SceneManager.hpp
	MainMenuScene.hpp
	MegaMillionsScene.hpp
	PowerBallScene.hpp
src/
	FileManager.cpp
	LuckyNumberGenerator.cpp
	MegaMillionsNumberGenerator.cpp
	PowerBallNumberGenerator.cpp
	SceneManager.cpp
	MainMenuScene.cpp
	MegaMillionsScene.cpp
	PowerBallScene.cpp
	main.cpp
Assets/
	Data/
		megamillions.csv
		powerball.csv
	Sprites/
		mega_millions.png
		powerball.png
```

## Build

Prerequisites:
- g++ with C++17 support
- Raylib installed on your system (linked in the `Makefile`)

Build and run:

```
make
./lottery
```

The `Makefile` compiles sources under `src/` and links Raylib (`-lraylib -lGL -lm -lpthread -ldl -lrt -lX11`). Headers are in `include/`.

## Using The App

- From the main menu, choose Powerball or Mega Millions.
- Each generator scene automatically performs an initial roll.
- Click “Generate … Numbers” to roll again.
- Click the square button below any number to toggle its lock:
	- Locked numbers remain unchanged on subsequent rolls.
	- Unlocked numbers are regenerated.
- Each number shows a quality percentage beneath it; an overall average is displayed for the set.

## Notes & Limitations

- This tool is for exploration and learning only. Historical frequency does not predict future draws.
- CSV formats are expected to match the samples in `Assets/Data/` (first metadata columns are skipped; numeric fields follow).
- The UI is intentionally simple and focused on clarity.

## Roadmap
- Sets, a collection of lucky numbers used to print or share.
- Saving of lucky numbers to add to your "sets"
- Export/share generated sets
- Add simple settings (fonts, colors, themes?)


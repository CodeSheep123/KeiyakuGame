#ifndef KEIYAKU_GLOBAL_HPP_
#define KEIYAKU_GLOBAL_HPP_

#include "KeiyakuGame.hpp"

extern Keiyaku::KeiyakuGame* gGame;
extern sf::RenderWindow* gWindow;
extern Keiyaku::PathDatabase* gPathDatabase;
extern Keiyaku::ImageManager* gImageManager;
extern Keiyaku::TextureManager* gTextureManager;
extern Keiyaku::FontManager* gFontManager;
extern Keiyaku::KeybindManager* gKeybindManager;
extern Keiyaku::MusicManager* gMusicManager;

#endif
#pragma once

#include <array>

#include "lib/raylib_clean.h"

namespace janowski::paczki_cpp::colors {

constexpr Color ALICEBLUE_C = Color{240u, 248u, 255u, 255u};
constexpr Color ANTIQUEWHITE_C = Color{250u, 235u, 215u, 255u};
constexpr Color ANTIQUEWHITE1_C = Color{255u, 239u, 219u, 255u};
constexpr Color ANTIQUEWHITE2_C = Color{238u, 223u, 204u, 255u};
constexpr Color ANTIQUEWHITE3_C = Color{205u, 192u, 176u, 255u};
constexpr Color ANTIQUEWHITE4_C = Color{139u, 131u, 120u, 255u};
constexpr Color AQUA_C = Color{0u, 255u, 255u, 255u};
constexpr Color AQUAMARINE1_C = Color{127u, 255u, 212u, 255u};
constexpr Color AQUAMARINE2_C = Color{118u, 238u, 198u, 255u};
constexpr Color AQUAMARINE3_C = Color{102u, 205u, 170u, 255u};
constexpr Color AQUAMARINE4_C = Color{69u, 139u, 116u, 255u};
constexpr Color AZURE1_C = Color{240u, 255u, 255u, 255u};
constexpr Color AZURE2_C = Color{224u, 238u, 238u, 255u};
constexpr Color AZURE3_C = Color{193u, 205u, 205u, 255u};
constexpr Color AZURE4_C = Color{131u, 139u, 139u, 255u};
constexpr Color BANANA_C = Color{227u, 207u, 87u, 255u};
constexpr Color BEIGE_C = Color{245u, 245u, 220u, 255u};
constexpr Color BISQUE1_C = Color{255u, 228u, 196u, 255u};
constexpr Color BISQUE2_C = Color{238u, 213u, 183u, 255u};
constexpr Color BISQUE3_C = Color{205u, 183u, 158u, 255u};
constexpr Color BISQUE4_C = Color{139u, 125u, 107u, 255u};
// constexpr Color BLACK_C = Color{0u, 0u, 0u, 255u};
constexpr Color BLANCHEDALMOND_C = Color{255u, 235u, 205u, 255u};
constexpr Color BLUE_C = Color{0u, 0u, 255u, 255u};
constexpr Color BLUE2_C = Color{0u, 0u, 238u, 255u};
constexpr Color BLUE3_C = Color{0u, 0u, 205u, 255u};
constexpr Color BLUE4_C = Color{0u, 0u, 139u, 255u};
constexpr Color BLUEVIOLET_C = Color{138u, 43u, 226u, 255u};
constexpr Color BRICK_C = Color{156u, 102u, 31u, 255u};
constexpr Color BROWN_C = Color{165u, 42u, 42u, 255u};
constexpr Color BROWN1_C = Color{255u, 64u, 64u, 255u};
constexpr Color BROWN2_C = Color{238u, 59u, 59u, 255u};
constexpr Color BROWN3_C = Color{205u, 51u, 51u, 255u};
constexpr Color BROWN4_C = Color{139u, 35u, 35u, 255u};
constexpr Color BURLYWOOD_C = Color{222u, 184u, 135u, 255u};
constexpr Color BURLYWOOD1_C = Color{255u, 211u, 155u, 255u};
constexpr Color BURLYWOOD2_C = Color{238u, 197u, 145u, 255u};
constexpr Color BURLYWOOD3_C = Color{205u, 170u, 125u, 255u};
constexpr Color BURLYWOOD4_C = Color{139u, 115u, 85u, 255u};
constexpr Color BURNTSIENNA_C = Color{138u, 54u, 15u, 255u};
constexpr Color BURNTUMBER_C = Color{138u, 51u, 36u, 255u};
constexpr Color CADETBLUE_C = Color{95u, 158u, 160u, 255u};
constexpr Color CADETBLUE1_C = Color{152u, 245u, 255u, 255u};
constexpr Color CADETBLUE2_C = Color{142u, 229u, 238u, 255u};
constexpr Color CADETBLUE3_C = Color{122u, 197u, 205u, 255u};
constexpr Color CADETBLUE4_C = Color{83u, 134u, 139u, 255u};
constexpr Color CADMIUMORANGE_C = Color{255u, 97u, 3u, 255u};
constexpr Color CADMIUMYELLOW_C = Color{255u, 153u, 18u, 255u};
constexpr Color CARROT_C = Color{237u, 145u, 33u, 255u};
constexpr Color CHARTREUSE1_C = Color{127u, 255u, 0u, 255u};
constexpr Color CHARTREUSE2_C = Color{118u, 238u, 0u, 255u};
constexpr Color CHARTREUSE3_C = Color{102u, 205u, 0u, 255u};
constexpr Color CHARTREUSE4_C = Color{69u, 139u, 0u, 255u};
constexpr Color CHOCOLATE_C = Color{210u, 105u, 30u, 255u};
constexpr Color CHOCOLATE1_C = Color{255u, 127u, 36u, 255u};
constexpr Color CHOCOLATE2_C = Color{238u, 118u, 33u, 255u};
constexpr Color CHOCOLATE3_C = Color{205u, 102u, 29u, 255u};
constexpr Color CHOCOLATE4_C = Color{139u, 69u, 19u, 255u};
constexpr Color COBALT_C = Color{61u, 89u, 171u, 255u};
constexpr Color COBALTGREEN_C = Color{61u, 145u, 64u, 255u};
constexpr Color COLDGREY_C = Color{128u, 138u, 135u, 255u};
constexpr Color CORAL_C = Color{255u, 127u, 80u, 255u};
constexpr Color CORAL1_C = Color{255u, 114u, 86u, 255u};
constexpr Color CORAL2_C = Color{238u, 106u, 80u, 255u};
constexpr Color CORAL3_C = Color{205u, 91u, 69u, 255u};
constexpr Color CORAL4_C = Color{139u, 62u, 47u, 255u};
constexpr Color CORNFLOWERBLUE_C = Color{100u, 149u, 237u, 255u};
constexpr Color CORNSILK1_C = Color{255u, 248u, 220u, 255u};
constexpr Color CORNSILK2_C = Color{238u, 232u, 205u, 255u};
constexpr Color CORNSILK3_C = Color{205u, 200u, 177u, 255u};
constexpr Color CORNSILK4_C = Color{139u, 136u, 120u, 255u};
constexpr Color CRIMSON_C = Color{220u, 20u, 60u, 255u};
constexpr Color CYAN2_C = Color{0u, 238u, 238u, 255u};
constexpr Color CYAN3_C = Color{0u, 205u, 205u, 255u};
constexpr Color CYAN4_C = Color{0u, 139u, 139u, 255u};
constexpr Color DARKGOLDENROD_C = Color{184u, 134u, 11u, 255u};
constexpr Color DARKGOLDENROD1_C = Color{255u, 185u, 15u, 255u};
constexpr Color DARKGOLDENROD2_C = Color{238u, 173u, 14u, 255u};
constexpr Color DARKGOLDENROD3_C = Color{205u, 149u, 12u, 255u};
constexpr Color DARKGOLDENROD4_C = Color{139u, 101u, 8u, 255u};
constexpr Color DARKGRAY_C = Color{169u, 169u, 169u, 255u};
constexpr Color DARKGREEN_C = Color{0u, 100u, 0u, 255u};
constexpr Color DARKKHAKI_C = Color{189u, 183u, 107u, 255u};
constexpr Color DARKOLIVEGREEN_C = Color{85u, 107u, 47u, 255u};
constexpr Color DARKOLIVEGREEN1_C = Color{202u, 255u, 112u, 255u};
constexpr Color DARKOLIVEGREEN2_C = Color{188u, 238u, 104u, 255u};
constexpr Color DARKOLIVEGREEN3_C = Color{162u, 205u, 90u, 255u};
constexpr Color DARKOLIVEGREEN4_C = Color{110u, 139u, 61u, 255u};
constexpr Color DARKORANGE_C = Color{255u, 140u, 0u, 255u};
constexpr Color DARKORANGE1_C = Color{255u, 127u, 0u, 255u};
constexpr Color DARKORANGE2_C = Color{238u, 118u, 0u, 255u};
constexpr Color DARKORANGE3_C = Color{205u, 102u, 0u, 255u};
constexpr Color DARKORANGE4_C = Color{139u, 69u, 0u, 255u};
constexpr Color DARKORCHID_C = Color{153u, 50u, 204u, 255u};
constexpr Color DARKORCHID1_C = Color{191u, 62u, 255u, 255u};
constexpr Color DARKORCHID2_C = Color{178u, 58u, 238u, 255u};
constexpr Color DARKORCHID3_C = Color{154u, 50u, 205u, 255u};
constexpr Color DARKORCHID4_C = Color{104u, 34u, 139u, 255u};
constexpr Color DARKSALMON_C = Color{233u, 150u, 122u, 255u};
constexpr Color DARKSEAGREEN_C = Color{143u, 188u, 143u, 255u};
constexpr Color DARKSEAGREEN1_C = Color{193u, 255u, 193u, 255u};
constexpr Color DARKSEAGREEN2_C = Color{180u, 238u, 180u, 255u};
constexpr Color DARKSEAGREEN3_C = Color{155u, 205u, 155u, 255u};
constexpr Color DARKSEAGREEN4_C = Color{105u, 139u, 105u, 255u};
constexpr Color DARKSLATEBLUE_C = Color{72u, 61u, 139u, 255u};
constexpr Color DARKSLATEGRAY_C = Color{47u, 79u, 79u, 255u};
constexpr Color DARKSLATEGRAY1_C = Color{151u, 255u, 255u, 255u};
constexpr Color DARKSLATEGRAY2_C = Color{141u, 238u, 238u, 255u};
constexpr Color DARKSLATEGRAY3_C = Color{121u, 205u, 205u, 255u};
constexpr Color DARKSLATEGRAY4_C = Color{82u, 139u, 139u, 255u};
constexpr Color DARKTURQUOISE_C = Color{0u, 206u, 209u, 255u};
constexpr Color DARKVIOLET_C = Color{148u, 0u, 211u, 255u};
constexpr Color DEEPPINK1_C = Color{255u, 20u, 147u, 255u};
constexpr Color DEEPPINK2_C = Color{238u, 18u, 137u, 255u};
constexpr Color DEEPPINK3_C = Color{205u, 16u, 118u, 255u};
constexpr Color DEEPPINK4_C = Color{139u, 10u, 80u, 255u};
constexpr Color DEEPSKYBLUE1_C = Color{0u, 191u, 255u, 255u};
constexpr Color DEEPSKYBLUE2_C = Color{0u, 178u, 238u, 255u};
constexpr Color DEEPSKYBLUE3_C = Color{0u, 154u, 205u, 255u};
constexpr Color DEEPSKYBLUE4_C = Color{0u, 104u, 139u, 255u};
constexpr Color DIMGRAY_C = Color{105u, 105u, 105u, 255u};
constexpr Color DODGERBLUE1_C = Color{30u, 144u, 255u, 255u};
constexpr Color DODGERBLUE2_C = Color{28u, 134u, 238u, 255u};
constexpr Color DODGERBLUE3_C = Color{24u, 116u, 205u, 255u};
constexpr Color DODGERBLUE4_C = Color{16u, 78u, 139u, 255u};
constexpr Color EGGSHELL_C = Color{252u, 230u, 201u, 255u};
constexpr Color EMERALDGREEN_C = Color{0u, 201u, 87u, 255u};
constexpr Color FIREBRICK_C = Color{178u, 34u, 34u, 255u};
constexpr Color FIREBRICK1_C = Color{255u, 48u, 48u, 255u};
constexpr Color FIREBRICK2_C = Color{238u, 44u, 44u, 255u};
constexpr Color FIREBRICK3_C = Color{205u, 38u, 38u, 255u};
constexpr Color FIREBRICK4_C = Color{139u, 26u, 26u, 255u};
constexpr Color FLESH_C = Color{255u, 125u, 64u, 255u};
constexpr Color FLORALWHITE_C = Color{255u, 250u, 240u, 255u};
constexpr Color FORESTGREEN_C = Color{34u, 139u, 34u, 255u};
constexpr Color GAINSBORO_C = Color{220u, 220u, 220u, 255u};
constexpr Color GHOSTWHITE_C = Color{248u, 248u, 255u, 255u};
constexpr Color GOLD1_C = Color{255u, 215u, 0u, 255u};
constexpr Color GOLD2_C = Color{238u, 201u, 0u, 255u};
constexpr Color GOLD3_C = Color{205u, 173u, 0u, 255u};
constexpr Color GOLD4_C = Color{139u, 117u, 0u, 255u};
constexpr Color GOLDENROD_C = Color{218u, 165u, 32u, 255u};
constexpr Color GOLDENROD1_C = Color{255u, 193u, 37u, 255u};
constexpr Color GOLDENROD2_C = Color{238u, 180u, 34u, 255u};
constexpr Color GOLDENROD3_C = Color{205u, 155u, 29u, 255u};
constexpr Color GOLDENROD4_C = Color{139u, 105u, 20u, 255u};
constexpr Color GRAY_C = Color{128u, 128u, 128u, 255u};
constexpr Color GRAY1_C = Color{3u, 3u, 3u, 255u};
constexpr Color GRAY10_C = Color{26u, 26u, 26u, 255u};
constexpr Color GRAY11_C = Color{28u, 28u, 28u, 255u};
constexpr Color GRAY12_C = Color{31u, 31u, 31u, 255u};
constexpr Color GRAY13_C = Color{33u, 33u, 33u, 255u};
constexpr Color GRAY14_C = Color{36u, 36u, 36u, 255u};
constexpr Color GRAY15_C = Color{38u, 38u, 38u, 255u};
constexpr Color GRAY16_C = Color{41u, 41u, 41u, 255u};
constexpr Color GRAY17_C = Color{43u, 43u, 43u, 255u};
constexpr Color GRAY18_C = Color{46u, 46u, 46u, 255u};
constexpr Color GRAY19_C = Color{48u, 48u, 48u, 255u};
constexpr Color GRAY2_C = Color{5u, 5u, 5u, 255u};
constexpr Color GRAY20_C = Color{51u, 51u, 51u, 255u};
constexpr Color GRAY21_C = Color{54u, 54u, 54u, 255u};
constexpr Color GRAY22_C = Color{56u, 56u, 56u, 255u};
constexpr Color GRAY23_C = Color{59u, 59u, 59u, 255u};
constexpr Color GRAY24_C = Color{61u, 61u, 61u, 255u};
constexpr Color GRAY25_C = Color{64u, 64u, 64u, 255u};
constexpr Color GRAY26_C = Color{66u, 66u, 66u, 255u};
constexpr Color GRAY27_C = Color{69u, 69u, 69u, 255u};
constexpr Color GRAY28_C = Color{71u, 71u, 71u, 255u};
constexpr Color GRAY29_C = Color{74u, 74u, 74u, 255u};
constexpr Color GRAY3_C = Color{8u, 8u, 8u, 255u};
constexpr Color GRAY30_C = Color{77u, 77u, 77u, 255u};
constexpr Color GRAY31_C = Color{79u, 79u, 79u, 255u};
constexpr Color GRAY32_C = Color{82u, 82u, 82u, 255u};
constexpr Color GRAY33_C = Color{84u, 84u, 84u, 255u};
constexpr Color GRAY34_C = Color{87u, 87u, 87u, 255u};
constexpr Color GRAY35_C = Color{89u, 89u, 89u, 255u};
constexpr Color GRAY36_C = Color{92u, 92u, 92u, 255u};
constexpr Color GRAY37_C = Color{94u, 94u, 94u, 255u};
constexpr Color GRAY38_C = Color{97u, 97u, 97u, 255u};
constexpr Color GRAY39_C = Color{99u, 99u, 99u, 255u};
constexpr Color GRAY4_C = Color{10u, 10u, 10u, 255u};
constexpr Color GRAY40_C = Color{102u, 102u, 102u, 255u};
constexpr Color GRAY42_C = Color{107u, 107u, 107u, 255u};
constexpr Color GRAY43_C = Color{110u, 110u, 110u, 255u};
constexpr Color GRAY44_C = Color{112u, 112u, 112u, 255u};
constexpr Color GRAY45_C = Color{115u, 115u, 115u, 255u};
constexpr Color GRAY46_C = Color{117u, 117u, 117u, 255u};
constexpr Color GRAY47_C = Color{120u, 120u, 120u, 255u};
constexpr Color GRAY48_C = Color{122u, 122u, 122u, 255u};
constexpr Color GRAY49_C = Color{125u, 125u, 125u, 255u};
constexpr Color GRAY5_C = Color{13u, 13u, 13u, 255u};
constexpr Color GRAY50_C = Color{127u, 127u, 127u, 255u};
constexpr Color GRAY51_C = Color{130u, 130u, 130u, 255u};
constexpr Color GRAY52_C = Color{133u, 133u, 133u, 255u};
constexpr Color GRAY53_C = Color{135u, 135u, 135u, 255u};
constexpr Color GRAY54_C = Color{138u, 138u, 138u, 255u};
constexpr Color GRAY55_C = Color{140u, 140u, 140u, 255u};
constexpr Color GRAY56_C = Color{143u, 143u, 143u, 255u};
constexpr Color GRAY57_C = Color{145u, 145u, 145u, 255u};
constexpr Color GRAY58_C = Color{148u, 148u, 148u, 255u};
constexpr Color GRAY59_C = Color{150u, 150u, 150u, 255u};
constexpr Color GRAY6_C = Color{15u, 15u, 15u, 255u};
constexpr Color GRAY60_C = Color{153u, 153u, 153u, 255u};
constexpr Color GRAY61_C = Color{156u, 156u, 156u, 255u};
constexpr Color GRAY62_C = Color{158u, 158u, 158u, 255u};
constexpr Color GRAY63_C = Color{161u, 161u, 161u, 255u};
constexpr Color GRAY64_C = Color{163u, 163u, 163u, 255u};
constexpr Color GRAY65_C = Color{166u, 166u, 166u, 255u};
constexpr Color GRAY66_C = Color{168u, 168u, 168u, 255u};
constexpr Color GRAY67_C = Color{171u, 171u, 171u, 255u};
constexpr Color GRAY68_C = Color{173u, 173u, 173u, 255u};
constexpr Color GRAY69_C = Color{176u, 176u, 176u, 255u};
constexpr Color GRAY7_C = Color{18u, 18u, 18u, 255u};
constexpr Color GRAY70_C = Color{179u, 179u, 179u, 255u};
constexpr Color GRAY71_C = Color{181u, 181u, 181u, 255u};
constexpr Color GRAY72_C = Color{184u, 184u, 184u, 255u};
constexpr Color GRAY73_C = Color{186u, 186u, 186u, 255u};
constexpr Color GRAY74_C = Color{189u, 189u, 189u, 255u};
constexpr Color GRAY75_C = Color{191u, 191u, 191u, 255u};
constexpr Color GRAY76_C = Color{194u, 194u, 194u, 255u};
constexpr Color GRAY77_C = Color{196u, 196u, 196u, 255u};
constexpr Color GRAY78_C = Color{199u, 199u, 199u, 255u};
constexpr Color GRAY79_C = Color{201u, 201u, 201u, 255u};
constexpr Color GRAY8_C = Color{20u, 20u, 20u, 255u};
constexpr Color GRAY80_C = Color{204u, 204u, 204u, 255u};
constexpr Color GRAY81_C = Color{207u, 207u, 207u, 255u};
constexpr Color GRAY82_C = Color{209u, 209u, 209u, 255u};
constexpr Color GRAY83_C = Color{212u, 212u, 212u, 255u};
constexpr Color GRAY84_C = Color{214u, 214u, 214u, 255u};
constexpr Color GRAY85_C = Color{217u, 217u, 217u, 255u};
constexpr Color GRAY86_C = Color{219u, 219u, 219u, 255u};
constexpr Color GRAY87_C = Color{222u, 222u, 222u, 255u};
constexpr Color GRAY88_C = Color{224u, 224u, 224u, 255u};
constexpr Color GRAY89_C = Color{227u, 227u, 227u, 255u};
constexpr Color GRAY9_C = Color{23u, 23u, 23u, 255u};
constexpr Color GRAY90_C = Color{229u, 229u, 229u, 255u};
constexpr Color GRAY91_C = Color{232u, 232u, 232u, 255u};
constexpr Color GRAY92_C = Color{235u, 235u, 235u, 255u};
constexpr Color GRAY93_C = Color{237u, 237u, 237u, 255u};
constexpr Color GRAY94_C = Color{240u, 240u, 240u, 255u};
constexpr Color GRAY95_C = Color{242u, 242u, 242u, 255u};
constexpr Color GRAY97_C = Color{247u, 247u, 247u, 255u};
constexpr Color GRAY98_C = Color{250u, 250u, 250u, 255u};
constexpr Color GRAY99_C = Color{252u, 252u, 252u, 255u};
constexpr Color GREEN_C = Color{0u, 128u, 0u, 255u};
constexpr Color GREEN1_C = Color{0u, 255u, 0u, 255u};
constexpr Color GREEN2_C = Color{0u, 238u, 0u, 255u};
constexpr Color GREEN3_C = Color{0u, 205u, 0u, 255u};
constexpr Color GREEN4_C = Color{0u, 139u, 0u, 255u};
constexpr Color GREENYELLOW_C = Color{173u, 255u, 47u, 255u};
constexpr Color HONEYDEW1_C = Color{240u, 255u, 240u, 255u};
constexpr Color HONEYDEW2_C = Color{224u, 238u, 224u, 255u};
constexpr Color HONEYDEW3_C = Color{193u, 205u, 193u, 255u};
constexpr Color HONEYDEW4_C = Color{131u, 139u, 131u, 255u};
constexpr Color HOTPINK_C = Color{255u, 105u, 180u, 255u};
constexpr Color HOTPINK1_C = Color{255u, 110u, 180u, 255u};
constexpr Color HOTPINK2_C = Color{238u, 106u, 167u, 255u};
constexpr Color HOTPINK3_C = Color{205u, 96u, 144u, 255u};
constexpr Color HOTPINK4_C = Color{139u, 58u, 98u, 255u};
constexpr Color INDIANRED_C = Color{176u, 23u, 31u, 255u};
constexpr Color INDIANRED1_C = Color{255u, 106u, 106u, 255u};
constexpr Color INDIANRED2_C = Color{238u, 99u, 99u, 255u};
constexpr Color INDIANRED3_C = Color{205u, 85u, 85u, 255u};
constexpr Color INDIANRED4_C = Color{139u, 58u, 58u, 255u};
constexpr Color INDIGO_C = Color{75u, 0u, 130u, 255u};
constexpr Color IVORY1_C = Color{255u, 255u, 240u, 255u};
constexpr Color IVORY2_C = Color{238u, 238u, 224u, 255u};
constexpr Color IVORY3_C = Color{205u, 205u, 193u, 255u};
constexpr Color IVORY4_C = Color{139u, 139u, 131u, 255u};
constexpr Color IVORYBLACK_C = Color{41u, 36u, 33u, 255u};
constexpr Color KHAKI_C = Color{240u, 230u, 140u, 255u};
constexpr Color KHAKI1_C = Color{255u, 246u, 143u, 255u};
constexpr Color KHAKI2_C = Color{238u, 230u, 133u, 255u};
constexpr Color KHAKI3_C = Color{205u, 198u, 115u, 255u};
constexpr Color KHAKI4_C = Color{139u, 134u, 78u, 255u};
constexpr Color LAVENDER_C = Color{230u, 230u, 250u, 255u};
constexpr Color LAVENDERBLUSH1_C = Color{255u, 240u, 245u, 255u};
constexpr Color LAVENDERBLUSH2_C = Color{238u, 224u, 229u, 255u};
constexpr Color LAVENDERBLUSH3_C = Color{205u, 193u, 197u, 255u};
constexpr Color LAVENDERBLUSH4_C = Color{139u, 131u, 134u, 255u};
constexpr Color LAWNGREEN_C = Color{124u, 252u, 0u, 255u};
constexpr Color LEMONCHIFFON1_C = Color{255u, 250u, 205u, 255u};
constexpr Color LEMONCHIFFON2_C = Color{238u, 233u, 191u, 255u};
constexpr Color LEMONCHIFFON3_C = Color{205u, 201u, 165u, 255u};
constexpr Color LEMONCHIFFON4_C = Color{139u, 137u, 112u, 255u};
constexpr Color LIGHTBLUE_C = Color{173u, 216u, 230u, 255u};
constexpr Color LIGHTBLUE1_C = Color{191u, 239u, 255u, 255u};
constexpr Color LIGHTBLUE2_C = Color{178u, 223u, 238u, 255u};
constexpr Color LIGHTBLUE3_C = Color{154u, 192u, 205u, 255u};
constexpr Color LIGHTBLUE4_C = Color{104u, 131u, 139u, 255u};
constexpr Color LIGHTCORAL_C = Color{240u, 128u, 128u, 255u};
constexpr Color LIGHTCYAN1_C = Color{224u, 255u, 255u, 255u};
constexpr Color LIGHTCYAN2_C = Color{209u, 238u, 238u, 255u};
constexpr Color LIGHTCYAN3_C = Color{180u, 205u, 205u, 255u};
constexpr Color LIGHTCYAN4_C = Color{122u, 139u, 139u, 255u};
constexpr Color LIGHTGOLDENROD1_C = Color{255u, 236u, 139u, 255u};
constexpr Color LIGHTGOLDENROD2_C = Color{238u, 220u, 130u, 255u};
constexpr Color LIGHTGOLDENROD3_C = Color{205u, 190u, 112u, 255u};
constexpr Color LIGHTGOLDENROD4_C = Color{139u, 129u, 76u, 255u};
constexpr Color LIGHTGOLDENRODYELLOW_C = Color{250u, 250u, 210u, 255u};
constexpr Color LIGHTGREY_C = Color{211u, 211u, 211u, 255u};
constexpr Color LIGHTPINK_C = Color{255u, 182u, 193u, 255u};
constexpr Color LIGHTPINK1_C = Color{255u, 174u, 185u, 255u};
constexpr Color LIGHTPINK2_C = Color{238u, 162u, 173u, 255u};
constexpr Color LIGHTPINK3_C = Color{205u, 140u, 149u, 255u};
constexpr Color LIGHTPINK4_C = Color{139u, 95u, 101u, 255u};
constexpr Color LIGHTSALMON1_C = Color{255u, 160u, 122u, 255u};
constexpr Color LIGHTSALMON2_C = Color{238u, 149u, 114u, 255u};
constexpr Color LIGHTSALMON3_C = Color{205u, 129u, 98u, 255u};
constexpr Color LIGHTSALMON4_C = Color{139u, 87u, 66u, 255u};
constexpr Color LIGHTSEAGREEN_C = Color{32u, 178u, 170u, 255u};
constexpr Color LIGHTSKYBLUE_C = Color{135u, 206u, 250u, 255u};
constexpr Color LIGHTSKYBLUE1_C = Color{176u, 226u, 255u, 255u};
constexpr Color LIGHTSKYBLUE2_C = Color{164u, 211u, 238u, 255u};
constexpr Color LIGHTSKYBLUE3_C = Color{141u, 182u, 205u, 255u};
constexpr Color LIGHTSKYBLUE4_C = Color{96u, 123u, 139u, 255u};
constexpr Color LIGHTSLATEBLUE_C = Color{132u, 112u, 255u, 255u};
constexpr Color LIGHTSLATEGRAY_C = Color{119u, 136u, 153u, 255u};
constexpr Color LIGHTSTEELBLUE_C = Color{176u, 196u, 222u, 255u};
constexpr Color LIGHTSTEELBLUE1_C = Color{202u, 225u, 255u, 255u};
constexpr Color LIGHTSTEELBLUE2_C = Color{188u, 210u, 238u, 255u};
constexpr Color LIGHTSTEELBLUE3_C = Color{162u, 181u, 205u, 255u};
constexpr Color LIGHTSTEELBLUE4_C = Color{110u, 123u, 139u, 255u};
constexpr Color LIGHTYELLOW1_C = Color{255u, 255u, 224u, 255u};
constexpr Color LIGHTYELLOW2_C = Color{238u, 238u, 209u, 255u};
constexpr Color LIGHTYELLOW3_C = Color{205u, 205u, 180u, 255u};
constexpr Color LIGHTYELLOW4_C = Color{139u, 139u, 122u, 255u};
constexpr Color LIMEGREEN_C = Color{50u, 205u, 50u, 255u};
constexpr Color LINEN_C = Color{250u, 240u, 230u, 255u};
constexpr Color MAGENTA_C = Color{255u, 0u, 255u, 255u};
constexpr Color MAGENTA2_C = Color{238u, 0u, 238u, 255u};
constexpr Color MAGENTA3_C = Color{205u, 0u, 205u, 255u};
constexpr Color MAGENTA4_C = Color{139u, 0u, 139u, 255u};
constexpr Color MANGANESEBLUE_C = Color{3u, 168u, 158u, 255u};
constexpr Color MAROON_C = Color{128u, 0u, 0u, 255u};
constexpr Color MAROON1_C = Color{255u, 52u, 179u, 255u};
constexpr Color MAROON2_C = Color{238u, 48u, 167u, 255u};
constexpr Color MAROON3_C = Color{205u, 41u, 144u, 255u};
constexpr Color MAROON4_C = Color{139u, 28u, 98u, 255u};
constexpr Color MEDIUMORCHID_C = Color{186u, 85u, 211u, 255u};
constexpr Color MEDIUMORCHID1_C = Color{224u, 102u, 255u, 255u};
constexpr Color MEDIUMORCHID2_C = Color{209u, 95u, 238u, 255u};
constexpr Color MEDIUMORCHID3_C = Color{180u, 82u, 205u, 255u};
constexpr Color MEDIUMORCHID4_C = Color{122u, 55u, 139u, 255u};
constexpr Color MEDIUMPURPLE_C = Color{147u, 112u, 219u, 255u};
constexpr Color MEDIUMPURPLE1_C = Color{171u, 130u, 255u, 255u};
constexpr Color MEDIUMPURPLE2_C = Color{159u, 121u, 238u, 255u};
constexpr Color MEDIUMPURPLE3_C = Color{137u, 104u, 205u, 255u};
constexpr Color MEDIUMPURPLE4_C = Color{93u, 71u, 139u, 255u};
constexpr Color MEDIUMSEAGREEN_C = Color{60u, 179u, 113u, 255u};
constexpr Color MEDIUMSLATEBLUE_C = Color{123u, 104u, 238u, 255u};
constexpr Color MEDIUMSPRINGGREEN_C = Color{0u, 250u, 154u, 255u};
constexpr Color MEDIUMTURQUOISE_C = Color{72u, 209u, 204u, 255u};
constexpr Color MEDIUMVIOLETRED_C = Color{199u, 21u, 133u, 255u};
constexpr Color MELON_C = Color{227u, 168u, 105u, 255u};
constexpr Color MIDNIGHTBLUE_C = Color{25u, 25u, 112u, 255u};
constexpr Color MINT_C = Color{189u, 252u, 201u, 255u};
constexpr Color MINTCREAM_C = Color{245u, 255u, 250u, 255u};
constexpr Color MISTYROSE1_C = Color{255u, 228u, 225u, 255u};
constexpr Color MISTYROSE2_C = Color{238u, 213u, 210u, 255u};
constexpr Color MISTYROSE3_C = Color{205u, 183u, 181u, 255u};
constexpr Color MISTYROSE4_C = Color{139u, 125u, 123u, 255u};
constexpr Color MOCCASIN_C = Color{255u, 228u, 181u, 255u};
constexpr Color NAVAJOWHITE1_C = Color{255u, 222u, 173u, 255u};
constexpr Color NAVAJOWHITE2_C = Color{238u, 207u, 161u, 255u};
constexpr Color NAVAJOWHITE3_C = Color{205u, 179u, 139u, 255u};
constexpr Color NAVAJOWHITE4_C = Color{139u, 121u, 94u, 255u};
constexpr Color NAVY_C = Color{0u, 0u, 128u, 255u};
constexpr Color OLDLACE_C = Color{253u, 245u, 230u, 255u};
constexpr Color OLIVE_C = Color{128u, 128u, 0u, 255u};
constexpr Color OLIVEDRAB_C = Color{107u, 142u, 35u, 255u};
constexpr Color OLIVEDRAB1_C = Color{192u, 255u, 62u, 255u};
constexpr Color OLIVEDRAB2_C = Color{179u, 238u, 58u, 255u};
constexpr Color OLIVEDRAB3_C = Color{154u, 205u, 50u, 255u};
constexpr Color OLIVEDRAB4_C = Color{105u, 139u, 34u, 255u};
constexpr Color ORANGE_C = Color{255u, 128u, 0u, 255u};
constexpr Color ORANGE1_C = Color{255u, 165u, 0u, 255u};
constexpr Color ORANGE2_C = Color{238u, 154u, 0u, 255u};
constexpr Color ORANGE3_C = Color{205u, 133u, 0u, 255u};
constexpr Color ORANGE4_C = Color{139u, 90u, 0u, 255u};
constexpr Color ORANGERED1_C = Color{255u, 69u, 0u, 255u};
constexpr Color ORANGERED2_C = Color{238u, 64u, 0u, 255u};
constexpr Color ORANGERED3_C = Color{205u, 55u, 0u, 255u};
constexpr Color ORANGERED4_C = Color{139u, 37u, 0u, 255u};
constexpr Color ORCHID_C = Color{218u, 112u, 214u, 255u};
constexpr Color ORCHID1_C = Color{255u, 131u, 250u, 255u};
constexpr Color ORCHID2_C = Color{238u, 122u, 233u, 255u};
constexpr Color ORCHID3_C = Color{205u, 105u, 201u, 255u};
constexpr Color ORCHID4_C = Color{139u, 71u, 137u, 255u};
constexpr Color PALEGOLDENROD_C = Color{238u, 232u, 170u, 255u};
constexpr Color PALEGREEN_C = Color{152u, 251u, 152u, 255u};
constexpr Color PALEGREEN1_C = Color{154u, 255u, 154u, 255u};
constexpr Color PALEGREEN2_C = Color{144u, 238u, 144u, 255u};
constexpr Color PALEGREEN3_C = Color{124u, 205u, 124u, 255u};
constexpr Color PALEGREEN4_C = Color{84u, 139u, 84u, 255u};
constexpr Color PALETURQUOISE1_C = Color{187u, 255u, 255u, 255u};
constexpr Color PALETURQUOISE2_C = Color{174u, 238u, 238u, 255u};
constexpr Color PALETURQUOISE3_C = Color{150u, 205u, 205u, 255u};
constexpr Color PALETURQUOISE4_C = Color{102u, 139u, 139u, 255u};
constexpr Color PALEVIOLETRED_C = Color{219u, 112u, 147u, 255u};
constexpr Color PALEVIOLETRED1_C = Color{255u, 130u, 171u, 255u};
constexpr Color PALEVIOLETRED2_C = Color{238u, 121u, 159u, 255u};
constexpr Color PALEVIOLETRED3_C = Color{205u, 104u, 137u, 255u};
constexpr Color PALEVIOLETRED4_C = Color{139u, 71u, 93u, 255u};
constexpr Color PAPAYAWHIP_C = Color{255u, 239u, 213u, 255u};
constexpr Color PEACHPUFF1_C = Color{255u, 218u, 185u, 255u};
constexpr Color PEACHPUFF2_C = Color{238u, 203u, 173u, 255u};
constexpr Color PEACHPUFF3_C = Color{205u, 175u, 149u, 255u};
constexpr Color PEACHPUFF4_C = Color{139u, 119u, 101u, 255u};
constexpr Color PEACOCK_C = Color{51u, 161u, 201u, 255u};
constexpr Color PINK_C = Color{255u, 192u, 203u, 255u};
constexpr Color PINK1_C = Color{255u, 181u, 197u, 255u};
constexpr Color PINK2_C = Color{238u, 169u, 184u, 255u};
constexpr Color PINK3_C = Color{205u, 145u, 158u, 255u};
constexpr Color PINK4_C = Color{139u, 99u, 108u, 255u};
constexpr Color PLUM_C = Color{221u, 160u, 221u, 255u};
constexpr Color PLUM1_C = Color{255u, 187u, 255u, 255u};
constexpr Color PLUM2_C = Color{238u, 174u, 238u, 255u};
constexpr Color PLUM3_C = Color{205u, 150u, 205u, 255u};
constexpr Color PLUM4_C = Color{139u, 102u, 139u, 255u};
constexpr Color POWDERBLUE_C = Color{176u, 224u, 230u, 255u};
constexpr Color PURPLE_C = Color{128u, 0u, 128u, 255u};
constexpr Color PURPLE1_C = Color{155u, 48u, 255u, 255u};
constexpr Color PURPLE2_C = Color{145u, 44u, 238u, 255u};
constexpr Color PURPLE3_C = Color{125u, 38u, 205u, 255u};
constexpr Color PURPLE4_C = Color{85u, 26u, 139u, 255u};
constexpr Color RASPBERRY_C = Color{135u, 38u, 87u, 255u};
constexpr Color RAWSIENNA_C = Color{199u, 97u, 20u, 255u};
// constexpr Color RED1_C = Color{255u, 0u, 0u, 255u};
constexpr Color RED2_C = Color{238u, 0u, 0u, 255u};
constexpr Color RED3_C = Color{205u, 0u, 0u, 255u};
constexpr Color RED4_C = Color{139u, 0u, 0u, 255u};
constexpr Color ROSYBROWN_C = Color{188u, 143u, 143u, 255u};
constexpr Color ROSYBROWN1_C = Color{255u, 193u, 193u, 255u};
constexpr Color ROSYBROWN2_C = Color{238u, 180u, 180u, 255u};
constexpr Color ROSYBROWN3_C = Color{205u, 155u, 155u, 255u};
constexpr Color ROSYBROWN4_C = Color{139u, 105u, 105u, 255u};
constexpr Color ROYALBLUE_C = Color{65u, 105u, 225u, 255u};
constexpr Color ROYALBLUE1_C = Color{72u, 118u, 255u, 255u};
constexpr Color ROYALBLUE2_C = Color{67u, 110u, 238u, 255u};
constexpr Color ROYALBLUE3_C = Color{58u, 95u, 205u, 255u};
constexpr Color ROYALBLUE4_C = Color{39u, 64u, 139u, 255u};
constexpr Color SALMON_C = Color{250u, 128u, 114u, 255u};
constexpr Color SALMON1_C = Color{255u, 140u, 105u, 255u};
constexpr Color SALMON2_C = Color{238u, 130u, 98u, 255u};
constexpr Color SALMON3_C = Color{205u, 112u, 84u, 255u};
constexpr Color SALMON4_C = Color{139u, 76u, 57u, 255u};
constexpr Color SANDYBROWN_C = Color{244u, 164u, 96u, 255u};
constexpr Color SAPGREEN_C = Color{48u, 128u, 20u, 255u};
constexpr Color SEAGREEN1_C = Color{84u, 255u, 159u, 255u};
constexpr Color SEAGREEN2_C = Color{78u, 238u, 148u, 255u};
constexpr Color SEAGREEN3_C = Color{67u, 205u, 128u, 255u};
constexpr Color SEAGREEN4_C = Color{46u, 139u, 87u, 255u};
constexpr Color SEASHELL1_C = Color{255u, 245u, 238u, 255u};
constexpr Color SEASHELL2_C = Color{238u, 229u, 222u, 255u};
constexpr Color SEASHELL3_C = Color{205u, 197u, 191u, 255u};
constexpr Color SEASHELL4_C = Color{139u, 134u, 130u, 255u};
constexpr Color SEPIA_C = Color{94u, 38u, 18u, 255u};
constexpr Color SGIBEET_C = Color{142u, 56u, 142u, 255u};
constexpr Color SGIBRIGHTGRAY_C = Color{197u, 193u, 170u, 255u};
constexpr Color SGICHARTREUSE_C = Color{113u, 198u, 113u, 255u};
constexpr Color SGIDARKGRAY_C = Color{85u, 85u, 85u, 255u};
constexpr Color SGIGRAY12_C = Color{30u, 30u, 30u, 255u};
constexpr Color SGIGRAY16_C = Color{40u, 40u, 40u, 255u};
constexpr Color SGIGRAY32_C = Color{81u, 81u, 81u, 255u};
constexpr Color SGIGRAY36_C = Color{91u, 91u, 91u, 255u};
constexpr Color SGIGRAY52_C = Color{132u, 132u, 132u, 255u};
constexpr Color SGIGRAY56_C = Color{142u, 142u, 142u, 255u};
constexpr Color SGIGRAY72_C = Color{183u, 183u, 183u, 255u};
constexpr Color SGIGRAY76_C = Color{193u, 193u, 193u, 255u};
constexpr Color SGIGRAY92_C = Color{234u, 234u, 234u, 255u};
constexpr Color SGIGRAY96_C = Color{244u, 244u, 244u, 255u};
constexpr Color SGILIGHTBLUE_C = Color{125u, 158u, 192u, 255u};
constexpr Color SGILIGHTGRAY_C = Color{170u, 170u, 170u, 255u};
constexpr Color SGIOLIVEDRAB_C = Color{142u, 142u, 56u, 255u};
constexpr Color SGISALMON_C = Color{198u, 113u, 113u, 255u};
constexpr Color SGISLATEBLUE_C = Color{113u, 113u, 198u, 255u};
constexpr Color SGITEAL_C = Color{56u, 142u, 142u, 255u};
constexpr Color SIENNA_C = Color{160u, 82u, 45u, 255u};
constexpr Color SIENNA1_C = Color{255u, 130u, 71u, 255u};
constexpr Color SIENNA2_C = Color{238u, 121u, 66u, 255u};
constexpr Color SIENNA3_C = Color{205u, 104u, 57u, 255u};
constexpr Color SIENNA4_C = Color{139u, 71u, 38u, 255u};
constexpr Color SILVER_C = Color{192u, 192u, 192u, 255u};
constexpr Color SKYBLUE_C = Color{135u, 206u, 235u, 255u};
constexpr Color SKYBLUE1_C = Color{135u, 206u, 255u, 255u};
constexpr Color SKYBLUE2_C = Color{126u, 192u, 238u, 255u};
constexpr Color SKYBLUE3_C = Color{108u, 166u, 205u, 255u};
constexpr Color SKYBLUE4_C = Color{74u, 112u, 139u, 255u};
constexpr Color SLATEBLUE_C = Color{106u, 90u, 205u, 255u};
constexpr Color SLATEBLUE1_C = Color{131u, 111u, 255u, 255u};
constexpr Color SLATEBLUE2_C = Color{122u, 103u, 238u, 255u};
constexpr Color SLATEBLUE3_C = Color{105u, 89u, 205u, 255u};
constexpr Color SLATEBLUE4_C = Color{71u, 60u, 139u, 255u};
constexpr Color SLATEGRAY_C = Color{112u, 128u, 144u, 255u};
constexpr Color SLATEGRAY1_C = Color{198u, 226u, 255u, 255u};
constexpr Color SLATEGRAY2_C = Color{185u, 211u, 238u, 255u};
constexpr Color SLATEGRAY3_C = Color{159u, 182u, 205u, 255u};
constexpr Color SLATEGRAY4_C = Color{108u, 123u, 139u, 255u};
constexpr Color SNOW1_C = Color{255u, 250u, 250u, 255u};
constexpr Color SNOW2_C = Color{238u, 233u, 233u, 255u};
constexpr Color SNOW3_C = Color{205u, 201u, 201u, 255u};
constexpr Color SNOW4_C = Color{139u, 137u, 137u, 255u};
constexpr Color SPRINGGREEN_C = Color{0u, 255u, 127u, 255u};
constexpr Color SPRINGGREEN1_C = Color{0u, 238u, 118u, 255u};
constexpr Color SPRINGGREEN2_C = Color{0u, 205u, 102u, 255u};
constexpr Color SPRINGGREEN3_C = Color{0u, 139u, 69u, 255u};
constexpr Color STEELBLUE_C = Color{70u, 130u, 180u, 255u};
constexpr Color STEELBLUE1_C = Color{99u, 184u, 255u, 255u};
constexpr Color STEELBLUE2_C = Color{92u, 172u, 238u, 255u};
constexpr Color STEELBLUE3_C = Color{79u, 148u, 205u, 255u};
constexpr Color STEELBLUE4_C = Color{54u, 100u, 139u, 255u};
constexpr Color TAN_C = Color{210u, 180u, 140u, 255u};
constexpr Color TAN1_C = Color{255u, 165u, 79u, 255u};
constexpr Color TAN2_C = Color{238u, 154u, 73u, 255u};
constexpr Color TAN3_C = Color{205u, 133u, 63u, 255u};
constexpr Color TAN4_C = Color{139u, 90u, 43u, 255u};
constexpr Color TEAL_C = Color{0u, 128u, 128u, 255u};
constexpr Color THISTLE_C = Color{216u, 191u, 216u, 255u};
constexpr Color THISTLE1_C = Color{255u, 225u, 255u, 255u};
constexpr Color THISTLE2_C = Color{238u, 210u, 238u, 255u};
constexpr Color THISTLE3_C = Color{205u, 181u, 205u, 255u};
constexpr Color THISTLE4_C = Color{139u, 123u, 139u, 255u};
constexpr Color TOMATO1_C = Color{255u, 99u, 71u, 255u};
constexpr Color TOMATO2_C = Color{238u, 92u, 66u, 255u};
constexpr Color TOMATO3_C = Color{205u, 79u, 57u, 255u};
constexpr Color TOMATO4_C = Color{139u, 54u, 38u, 255u};
constexpr Color TURQUOISE_C = Color{64u, 224u, 208u, 255u};
constexpr Color TURQUOISE1_C = Color{0u, 245u, 255u, 255u};
constexpr Color TURQUOISE2_C = Color{0u, 229u, 238u, 255u};
constexpr Color TURQUOISE3_C = Color{0u, 197u, 205u, 255u};
constexpr Color TURQUOISE4_C = Color{0u, 134u, 139u, 255u};
constexpr Color TURQUOISEBLUE_C = Color{0u, 199u, 140u, 255u};
constexpr Color VIOLET_C = Color{238u, 130u, 238u, 255u};
constexpr Color VIOLETRED_C = Color{208u, 32u, 144u, 255u};
constexpr Color VIOLETRED1_C = Color{255u, 62u, 150u, 255u};
constexpr Color VIOLETRED2_C = Color{238u, 58u, 140u, 255u};
constexpr Color VIOLETRED3_C = Color{205u, 50u, 120u, 255u};
constexpr Color VIOLETRED4_C = Color{139u, 34u, 82u, 255u};
constexpr Color WARMGREY_C = Color{128u, 128u, 105u, 255u};
constexpr Color WHEAT_C = Color{245u, 222u, 179u, 255u};
constexpr Color WHEAT1_C = Color{255u, 231u, 186u, 255u};
constexpr Color WHEAT2_C = Color{238u, 216u, 174u, 255u};
constexpr Color WHEAT3_C = Color{205u, 186u, 150u, 255u};
constexpr Color WHEAT4_C = Color{139u, 126u, 102u, 255u};
constexpr Color WHITE_C = Color{255u, 255u, 255u, 255u};
constexpr Color WHITESMOKE_C = Color{245u, 245u, 245u, 255u};
constexpr Color YELLOW1_C = Color{255u, 255u, 0u, 255u};
constexpr Color YELLOW2_C = Color{238u, 238u, 0u, 255u};
constexpr Color YELLOW3_C = Color{205u, 205u, 0u, 255u};
constexpr Color YELLOW4_C = Color{139u, 139u, 0u, 255u};

static constexpr std::array<Color, 551> kColors{
    ALICEBLUE_C,
    ANTIQUEWHITE_C,
    ANTIQUEWHITE1_C,
    ANTIQUEWHITE2_C,
    ANTIQUEWHITE3_C,
    ANTIQUEWHITE4_C,
    AQUA_C,
    AQUAMARINE1_C,
    AQUAMARINE2_C,
    AQUAMARINE3_C,
    AQUAMARINE4_C,
    AZURE1_C,
    AZURE2_C,
    AZURE3_C,
    AZURE4_C,
    BANANA_C,
    BEIGE_C,
    BISQUE1_C,
    BISQUE2_C,
    BISQUE3_C,
    BISQUE4_C,
    // BLACK_C,
    BLANCHEDALMOND_C,
    BLUE_C,
    BLUE2_C,
    BLUE3_C,
    BLUE4_C,
    BLUEVIOLET_C,
    BRICK_C,
    BROWN_C,
    BROWN1_C,
    BROWN2_C,
    BROWN3_C,
    BROWN4_C,
    BURLYWOOD_C,
    BURLYWOOD1_C,
    BURLYWOOD2_C,
    BURLYWOOD3_C,
    BURLYWOOD4_C,
    BURNTSIENNA_C,
    BURNTUMBER_C,
    CADETBLUE_C,
    CADETBLUE1_C,
    CADETBLUE2_C,
    CADETBLUE3_C,
    CADETBLUE4_C,
    CADMIUMORANGE_C,
    CADMIUMYELLOW_C,
    CARROT_C,
    CHARTREUSE1_C,
    CHARTREUSE2_C,
    CHARTREUSE3_C,
    CHARTREUSE4_C,
    CHOCOLATE_C,
    CHOCOLATE1_C,
    CHOCOLATE2_C,
    CHOCOLATE3_C,
    CHOCOLATE4_C,
    COBALT_C,
    COBALTGREEN_C,
    COLDGREY_C,
    CORAL_C,
    CORAL1_C,
    CORAL2_C,
    CORAL3_C,
    CORAL4_C,
    CORNFLOWERBLUE_C,
    CORNSILK1_C,
    CORNSILK2_C,
    CORNSILK3_C,
    CORNSILK4_C,
    CRIMSON_C,
    CYAN2_C,
    CYAN3_C,
    CYAN4_C,
    DARKGOLDENROD_C,
    DARKGOLDENROD1_C,
    DARKGOLDENROD2_C,
    DARKGOLDENROD3_C,
    DARKGOLDENROD4_C,
    DARKGRAY_C,
    DARKGREEN_C,
    DARKKHAKI_C,
    DARKOLIVEGREEN_C,
    DARKOLIVEGREEN1_C,
    DARKOLIVEGREEN2_C,
    DARKOLIVEGREEN3_C,
    DARKOLIVEGREEN4_C,
    DARKORANGE_C,
    DARKORANGE1_C,
    DARKORANGE2_C,
    DARKORANGE3_C,
    DARKORANGE4_C,
    DARKORCHID_C,
    DARKORCHID1_C,
    DARKORCHID2_C,
    DARKORCHID3_C,
    DARKORCHID4_C,
    DARKSALMON_C,
    DARKSEAGREEN_C,
    DARKSEAGREEN1_C,
    DARKSEAGREEN2_C,
    DARKSEAGREEN3_C,
    DARKSEAGREEN4_C,
    DARKSLATEBLUE_C,
    DARKSLATEGRAY_C,
    DARKSLATEGRAY1_C,
    DARKSLATEGRAY2_C,
    DARKSLATEGRAY3_C,
    DARKSLATEGRAY4_C,
    DARKTURQUOISE_C,
    DARKVIOLET_C,
    DEEPPINK1_C,
    DEEPPINK2_C,
    DEEPPINK3_C,
    DEEPPINK4_C,
    DEEPSKYBLUE1_C,
    DEEPSKYBLUE2_C,
    DEEPSKYBLUE3_C,
    DEEPSKYBLUE4_C,
    DIMGRAY_C,
    DODGERBLUE1_C,
    DODGERBLUE2_C,
    DODGERBLUE3_C,
    DODGERBLUE4_C,
    EGGSHELL_C,
    EMERALDGREEN_C,
    FIREBRICK_C,
    FIREBRICK1_C,
    FIREBRICK2_C,
    FIREBRICK3_C,
    FIREBRICK4_C,
    FLESH_C,
    FLORALWHITE_C,
    FORESTGREEN_C,
    GAINSBORO_C,
    GHOSTWHITE_C,
    GOLD1_C,
    GOLD2_C,
    GOLD3_C,
    GOLD4_C,
    GOLDENROD_C,
    GOLDENROD1_C,
    GOLDENROD2_C,
    GOLDENROD3_C,
    GOLDENROD4_C,
    GRAY_C,
    GRAY1_C,
    GRAY10_C,
    GRAY11_C,
    GRAY12_C,
    GRAY13_C,
    GRAY14_C,
    GRAY15_C,
    GRAY16_C,
    GRAY17_C,
    GRAY18_C,
    GRAY19_C,
    GRAY2_C,
    GRAY20_C,
    GRAY21_C,
    GRAY22_C,
    GRAY23_C,
    GRAY24_C,
    GRAY25_C,
    GRAY26_C,
    GRAY27_C,
    GRAY28_C,
    GRAY29_C,
    GRAY3_C,
    GRAY30_C,
    GRAY31_C,
    GRAY32_C,
    GRAY33_C,
    GRAY34_C,
    GRAY35_C,
    GRAY36_C,
    GRAY37_C,
    GRAY38_C,
    GRAY39_C,
    GRAY4_C,
    GRAY40_C,
    GRAY42_C,
    GRAY43_C,
    GRAY44_C,
    GRAY45_C,
    GRAY46_C,
    GRAY47_C,
    GRAY48_C,
    GRAY49_C,
    GRAY5_C,
    GRAY50_C,
    GRAY51_C,
    GRAY52_C,
    GRAY53_C,
    GRAY54_C,
    GRAY55_C,
    GRAY56_C,
    GRAY57_C,
    GRAY58_C,
    GRAY59_C,
    GRAY6_C,
    GRAY60_C,
    GRAY61_C,
    GRAY62_C,
    GRAY63_C,
    GRAY64_C,
    GRAY65_C,
    GRAY66_C,
    GRAY67_C,
    GRAY68_C,
    GRAY69_C,
    GRAY7_C,
    GRAY70_C,
    GRAY71_C,
    GRAY72_C,
    GRAY73_C,
    GRAY74_C,
    GRAY75_C,
    GRAY76_C,
    GRAY77_C,
    GRAY78_C,
    GRAY79_C,
    GRAY8_C,
    GRAY80_C,
    GRAY81_C,
    GRAY82_C,
    GRAY83_C,
    GRAY84_C,
    GRAY85_C,
    GRAY86_C,
    GRAY87_C,
    GRAY88_C,
    GRAY89_C,
    GRAY9_C,
    GRAY90_C,
    GRAY91_C,
    GRAY92_C,
    GRAY93_C,
    GRAY94_C,
    GRAY95_C,
    GRAY97_C,
    GRAY98_C,
    GRAY99_C,
    GREEN_C,
    GREEN1_C,
    GREEN2_C,
    GREEN3_C,
    GREEN4_C,
    GREENYELLOW_C,
    HONEYDEW1_C,
    HONEYDEW2_C,
    HONEYDEW3_C,
    HONEYDEW4_C,
    HOTPINK_C,
    HOTPINK1_C,
    HOTPINK2_C,
    HOTPINK3_C,
    HOTPINK4_C,
    INDIANRED_C,
    INDIANRED1_C,
    INDIANRED2_C,
    INDIANRED3_C,
    INDIANRED4_C,
    INDIGO_C,
    IVORY1_C,
    IVORY2_C,
    IVORY3_C,
    IVORY4_C,
    IVORYBLACK_C,
    KHAKI_C,
    KHAKI1_C,
    KHAKI2_C,
    KHAKI3_C,
    KHAKI4_C,
    LAVENDER_C,
    LAVENDERBLUSH1_C,
    LAVENDERBLUSH2_C,
    LAVENDERBLUSH3_C,
    LAVENDERBLUSH4_C,
    LAWNGREEN_C,
    LEMONCHIFFON1_C,
    LEMONCHIFFON2_C,
    LEMONCHIFFON3_C,
    LEMONCHIFFON4_C,
    LIGHTBLUE_C,
    LIGHTBLUE1_C,
    LIGHTBLUE2_C,
    LIGHTBLUE3_C,
    LIGHTBLUE4_C,
    LIGHTCORAL_C,
    LIGHTCYAN1_C,
    LIGHTCYAN2_C,
    LIGHTCYAN3_C,
    LIGHTCYAN4_C,
    LIGHTGOLDENROD1_C,
    LIGHTGOLDENROD2_C,
    LIGHTGOLDENROD3_C,
    LIGHTGOLDENROD4_C,
    LIGHTGOLDENRODYELLOW_C,
    LIGHTGREY_C,
    LIGHTPINK_C,
    LIGHTPINK1_C,
    LIGHTPINK2_C,
    LIGHTPINK3_C,
    LIGHTPINK4_C,
    LIGHTSALMON1_C,
    LIGHTSALMON2_C,
    LIGHTSALMON3_C,
    LIGHTSALMON4_C,
    LIGHTSEAGREEN_C,
    LIGHTSKYBLUE_C,
    LIGHTSKYBLUE1_C,
    LIGHTSKYBLUE2_C,
    LIGHTSKYBLUE3_C,
    LIGHTSKYBLUE4_C,
    LIGHTSLATEBLUE_C,
    LIGHTSLATEGRAY_C,
    LIGHTSTEELBLUE_C,
    LIGHTSTEELBLUE1_C,
    LIGHTSTEELBLUE2_C,
    LIGHTSTEELBLUE3_C,
    LIGHTSTEELBLUE4_C,
    LIGHTYELLOW1_C,
    LIGHTYELLOW2_C,
    LIGHTYELLOW3_C,
    LIGHTYELLOW4_C,
    LIMEGREEN_C,
    LINEN_C,
    MAGENTA_C,
    MAGENTA2_C,
    MAGENTA3_C,
    MAGENTA4_C,
    MANGANESEBLUE_C,
    MAROON_C,
    MAROON1_C,
    MAROON2_C,
    MAROON3_C,
    MAROON4_C,
    MEDIUMORCHID_C,
    MEDIUMORCHID1_C,
    MEDIUMORCHID2_C,
    MEDIUMORCHID3_C,
    MEDIUMORCHID4_C,
    MEDIUMPURPLE_C,
    MEDIUMPURPLE1_C,
    MEDIUMPURPLE2_C,
    MEDIUMPURPLE3_C,
    MEDIUMPURPLE4_C,
    MEDIUMSEAGREEN_C,
    MEDIUMSLATEBLUE_C,
    MEDIUMSPRINGGREEN_C,
    MEDIUMTURQUOISE_C,
    MEDIUMVIOLETRED_C,
    MELON_C,
    MIDNIGHTBLUE_C,
    MINT_C,
    MINTCREAM_C,
    MISTYROSE1_C,
    MISTYROSE2_C,
    MISTYROSE3_C,
    MISTYROSE4_C,
    MOCCASIN_C,
    NAVAJOWHITE1_C,
    NAVAJOWHITE2_C,
    NAVAJOWHITE3_C,
    NAVAJOWHITE4_C,
    NAVY_C,
    OLDLACE_C,
    OLIVE_C,
    OLIVEDRAB_C,
    OLIVEDRAB1_C,
    OLIVEDRAB2_C,
    OLIVEDRAB3_C,
    OLIVEDRAB4_C,
    ORANGE_C,
    ORANGE1_C,
    ORANGE2_C,
    ORANGE3_C,
    ORANGE4_C,
    ORANGERED1_C,
    ORANGERED2_C,
    ORANGERED3_C,
    ORANGERED4_C,
    ORCHID_C,
    ORCHID1_C,
    ORCHID2_C,
    ORCHID3_C,
    ORCHID4_C,
    PALEGOLDENROD_C,
    PALEGREEN_C,
    PALEGREEN1_C,
    PALEGREEN2_C,
    PALEGREEN3_C,
    PALEGREEN4_C,
    PALETURQUOISE1_C,
    PALETURQUOISE2_C,
    PALETURQUOISE3_C,
    PALETURQUOISE4_C,
    PALEVIOLETRED_C,
    PALEVIOLETRED1_C,
    PALEVIOLETRED2_C,
    PALEVIOLETRED3_C,
    PALEVIOLETRED4_C,
    PAPAYAWHIP_C,
    PEACHPUFF1_C,
    PEACHPUFF2_C,
    PEACHPUFF3_C,
    PEACHPUFF4_C,
    PEACOCK_C,
    PINK_C,
    PINK1_C,
    PINK2_C,
    PINK3_C,
    PINK4_C,
    PLUM_C,
    PLUM1_C,
    PLUM2_C,
    PLUM3_C,
    PLUM4_C,
    POWDERBLUE_C,
    PURPLE_C,
    PURPLE1_C,
    PURPLE2_C,
    PURPLE3_C,
    PURPLE4_C,
    RASPBERRY_C,
    RAWSIENNA_C,
    // RED1_C,
    RED2_C,
    RED3_C,
    RED4_C,
    ROSYBROWN_C,
    ROSYBROWN1_C,
    ROSYBROWN2_C,
    ROSYBROWN3_C,
    ROSYBROWN4_C,
    ROYALBLUE_C,
    ROYALBLUE1_C,
    ROYALBLUE2_C,
    ROYALBLUE3_C,
    ROYALBLUE4_C,
    SALMON_C,
    SALMON1_C,
    SALMON2_C,
    SALMON3_C,
    SALMON4_C,
    SANDYBROWN_C,
    SAPGREEN_C,
    SEAGREEN1_C,
    SEAGREEN2_C,
    SEAGREEN3_C,
    SEAGREEN4_C,
    SEASHELL1_C,
    SEASHELL2_C,
    SEASHELL3_C,
    SEASHELL4_C,
    SEPIA_C,
    SGIBEET_C,
    SGIBRIGHTGRAY_C,
    SGICHARTREUSE_C,
    SGIDARKGRAY_C,
    SGIGRAY12_C,
    SGIGRAY16_C,
    SGIGRAY32_C,
    SGIGRAY36_C,
    SGIGRAY52_C,
    SGIGRAY56_C,
    SGIGRAY72_C,
    SGIGRAY76_C,
    SGIGRAY92_C,
    SGIGRAY96_C,
    SGILIGHTBLUE_C,
    SGILIGHTGRAY_C,
    SGIOLIVEDRAB_C,
    SGISALMON_C,
    SGISLATEBLUE_C,
    SGITEAL_C,
    SIENNA_C,
    SIENNA1_C,
    SIENNA2_C,
    SIENNA3_C,
    SIENNA4_C,
    SILVER_C,
    SKYBLUE_C,
    SKYBLUE1_C,
    SKYBLUE2_C,
    SKYBLUE3_C,
    SKYBLUE4_C,
    SLATEBLUE_C,
    SLATEBLUE1_C,
    SLATEBLUE2_C,
    SLATEBLUE3_C,
    SLATEBLUE4_C,
    SLATEGRAY_C,
    SLATEGRAY1_C,
    SLATEGRAY2_C,
    SLATEGRAY3_C,
    SLATEGRAY4_C,
    SNOW1_C,
    SNOW2_C,
    SNOW3_C,
    SNOW4_C,
    SPRINGGREEN_C,
    SPRINGGREEN1_C,
    SPRINGGREEN2_C,
    SPRINGGREEN3_C,
    STEELBLUE_C,
    STEELBLUE1_C,
    STEELBLUE2_C,
    STEELBLUE3_C,
    STEELBLUE4_C,
    TAN_C,
    TAN1_C,
    TAN2_C,
    TAN3_C,
    TAN4_C,
    TEAL_C,
    THISTLE_C,
    THISTLE1_C,
    THISTLE2_C,
    THISTLE3_C,
    THISTLE4_C,
    TOMATO1_C,
    TOMATO2_C,
    TOMATO3_C,
    TOMATO4_C,
    TURQUOISE_C,
    TURQUOISE1_C,
    TURQUOISE2_C,
    TURQUOISE3_C,
    TURQUOISE4_C,
    TURQUOISEBLUE_C,
    VIOLET_C,
    VIOLETRED_C,
    VIOLETRED1_C,
    VIOLETRED2_C,
    VIOLETRED3_C,
    VIOLETRED4_C,
    WARMGREY_C,
    WHEAT_C,
    WHEAT1_C,
    WHEAT2_C,
    WHEAT3_C,
    WHEAT4_C,
    WHITE_C,
    WHITESMOKE_C,
    YELLOW1_C,
    YELLOW2_C,
    YELLOW3_C,
    YELLOW4_C,
};

}  // namespace janowski::paczki_cpp::colors
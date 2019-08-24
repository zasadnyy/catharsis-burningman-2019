#ifndef PALETTES_H

DEFINE_GRADIENT_PALETTE( Purplefly_p ) {
    0,   0,  0,  0,
   63, 239,  0,122,
  191, 252,255, 78,
  255,   0,  0,  0
};

DEFINE_GRADIENT_PALETTE( Ukranian_flag_gp ) {
    0,   0,  0,255,
  127,   0,  0,255,
  127, 255,255,  0,
  255, 255,255,  0};

DEFINE_GRADIENT_PALETTE( rhubarb_gp ) {
    0, 255, 55, 45,
   76, 255,  0,  0,
  127, 188, 12, 45,
  191, 255,  0,  0,
  255, 188, 12, 45};


DEFINE_GRADIENT_PALETTE( black_red_black_gp ) {
    0,   0,  0,  0,
  127, 255,  0,  0,
  255,   0,  0,  0};



CRGBPalette16 palettes[] = {
    // Purplefly_p,
    Ukranian_flag_gp,
    rhubarb_gp,
    // black_red_black_gp,
    RainbowColors_p,
    // LavaColors_p,
    // CloudColors_p,
    // PartyColors_p,
};


#endif /* PALETTES_H */
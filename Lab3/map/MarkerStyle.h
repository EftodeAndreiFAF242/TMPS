// Lab 3 - Flyweight: the Flyweight, the look of the markers of one category, shared by all of them

#pragma once

#include <string>
#include <vector>

// The look of every marker of one category on the city map: the category and its icon. An icon is a
// picture of 32 x 32 pixels with 4 bytes per pixel, so it takes 4096 bytes. All the potholes on the
// map look the same, so they share one MarkerStyle instead of each marker keeping its own copy of
// the picture. This is the intrinsic state: it is the same for every marker that uses it, and it is
// const, so nobody can change it after it was made.
class MarkerStyle {
public:
    static const int ICON_SIZE = 32 * 32 * 4;  // the bytes of one icon

    explicit MarkerStyle(const std::string& category);

    // Draws one marker. The report number and the address are the extrinsic state: they are
    // different for every marker, so they are given here and never kept inside the style.
    void draw(int reportId, const std::string& address) const;

private:
    const std::string category;
    const std::vector<unsigned char> icon;  // the pixels of the picture
};

#pragma once

#include "styles.h"

// From https://github.com/procedural/gpulib/blob/master/gpulib_imgui.h
// https://github.com/ocornut/imgui/issues/707

namespace quant
{

void setDarkStyle() {

    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // --- Paleta moderna tipo Tailwind ---
    ImVec4 bg0   = ImVec4(0.12f, 0.13f, 0.15f, 1.00f); // fondo principal
    ImVec4 bg1   = ImVec4(0.16f, 0.17f, 0.20f, 1.00f); // paneles
    ImVec4 bg2   = ImVec4(0.21f, 0.22f, 0.25f, 1.00f); // hover
    ImVec4 accent= ImVec4(0.30f, 0.56f, 1.00f, 1.00f); // azul elegante
    ImVec4 text  = ImVec4(0.94f, 0.95f, 0.96f, 1.00f);
    ImVec4 border= ImVec4(0.26f, 0.27f, 0.30f, 1.00f);

    colors[ImGuiCol_Text]                   = text;
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.45f, 0.47f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = bg0;
    colors[ImGuiCol_ChildBg]                = bg1;
    colors[ImGuiCol_PopupBg]                = bg1;
    colors[ImGuiCol_Border]                 = border;
    colors[ImGuiCol_FrameBg]                = bg1;
    colors[ImGuiCol_FrameBgHovered]         = bg2;
    colors[ImGuiCol_FrameBgActive]          = accent;
    colors[ImGuiCol_TitleBg]                = bg1;
    colors[ImGuiCol_TitleBgActive]          = bg1;
    colors[ImGuiCol_MenuBarBg]              = bg1;
    colors[ImGuiCol_ScrollbarBg]            = bg0;
    colors[ImGuiCol_ScrollbarGrab]          = bg2;
    colors[ImGuiCol_ScrollbarGrabHovered]   = accent;
    colors[ImGuiCol_ScrollbarGrabActive]    = accent;
    colors[ImGuiCol_CheckMark]              = accent;
    colors[ImGuiCol_SliderGrab]             = accent;
    colors[ImGuiCol_SliderGrabActive]       = accent;
    colors[ImGuiCol_Button]                 = bg1;
    colors[ImGuiCol_ButtonHovered]          = bg2;
    colors[ImGuiCol_ButtonActive]           = accent;
    colors[ImGuiCol_Header]                 = bg1;
    colors[ImGuiCol_HeaderHovered]          = bg2;
    colors[ImGuiCol_HeaderActive]           = accent;
    colors[ImGuiCol_Separator]              = border;
    colors[ImGuiCol_Tab]                    = bg1;
    colors[ImGuiCol_TabHovered]             = accent;
    colors[ImGuiCol_TabActive]              = accent;
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(accent.x, accent.y, accent.z, 0.35f);
    colors[ImGuiCol_NavHighlight]           = accent;
    colors[ImGuiCol_FrameBg]                = bg1;
    colors[ImGuiCol_FrameBgHovered]         = bg2;
    colors[ImGuiCol_FrameBgActive]          = ImVec4(accent.x, accent.y, accent.z, 0.25f); 
    colors[ImGuiCol_SliderGrab]             = accent;
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(accent.x, accent.y, accent.z, 0.8f);

    // --- Espaciado y estética ---
    style.WindowPadding       = ImVec2(12, 12);
    style.FramePadding        = ImVec2(8, 6);
    style.ItemSpacing         = ImVec2(10, 8);
    style.WindowBorderSize    = 1.0f;
    style.FrameBorderSize     = 1.0f;
    style.PopupBorderSize     = 1.0f;
    style.WindowRounding      = 8.0f;
    style.FrameRounding       = 6.0f;
    style.ScrollbarRounding   = 12.0f;
    style.GrabRounding        = 6.0f;
    style.TabRounding         = 6.0f;
}

void setLightStyle() {

    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // --- Paleta elegante ---
    ImVec4 bg0    = ImVec4(0.97f, 0.98f, 0.99f, 1.00f); // fondo general
    ImVec4 bg1    = ImVec4(0.94f, 0.95f, 0.97f, 1.00f); // paneles
    ImVec4 bg2    = ImVec4(0.88f, 0.89f, 0.92f, 1.00f); // hover
    ImVec4 accent = ImVec4(0.37f, 0.68f, 1.00f, 1.00f); // azul pastel (como macOS)
    ImVec4 text   = ImVec4(0.15f, 0.17f, 0.20f, 1.00f); // gris oscuro (no negro)
    ImVec4 border = ImVec4(0.82f, 0.84f, 0.87f, 1.00f);

    // --- Colores base ---
    colors[ImGuiCol_Text]                   = text;
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.55f, 0.57f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg]               = bg0;
    colors[ImGuiCol_ChildBg]                = bg1;
    colors[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Border]                 = border;

    // --- Controles ---
    colors[ImGuiCol_FrameBg]                = bg1;
    colors[ImGuiCol_FrameBgHovered]         = bg2;
    colors[ImGuiCol_FrameBgActive]          = accent;
    colors[ImGuiCol_TitleBg]                = bg1;
    colors[ImGuiCol_TitleBgActive]          = bg1;
    colors[ImGuiCol_MenuBarBg]              = bg1;
    colors[ImGuiCol_ScrollbarBg]            = bg0;
    colors[ImGuiCol_ScrollbarGrab]          = bg2;
    colors[ImGuiCol_ScrollbarGrabHovered]   = accent;
    colors[ImGuiCol_ScrollbarGrabActive]    = accent;
    colors[ImGuiCol_CheckMark]              = accent;
    colors[ImGuiCol_SliderGrab]             = accent;
    colors[ImGuiCol_SliderGrabActive]       = accent;
    colors[ImGuiCol_Button]                 = bg1;
    colors[ImGuiCol_ButtonHovered]          = bg2;
    colors[ImGuiCol_ButtonActive]           = accent;
    colors[ImGuiCol_Header]                 = bg1;
    colors[ImGuiCol_HeaderHovered]          = bg2;
    colors[ImGuiCol_HeaderActive]           = accent;
    colors[ImGuiCol_Separator]              = border;
    colors[ImGuiCol_Tab]                    = bg1;
    colors[ImGuiCol_TabHovered]             = accent;
    colors[ImGuiCol_TabActive]              = accent;
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(accent.x, accent.y, accent.z, 0.25f);
    colors[ImGuiCol_NavHighlight]           = accent;
    colors[ImGuiCol_FrameBg]                = bg1;
    colors[ImGuiCol_FrameBgHovered]         = bg2;
    colors[ImGuiCol_FrameBgActive]          = ImVec4(accent.x, accent.y, accent.z, 0.25f);
    colors[ImGuiCol_SliderGrab]             = accent;
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(accent.x, accent.y, accent.z, 0.8f);

    // --- Estilo y proporciones ---
    style.WindowPadding       = ImVec2(12, 12);
    style.FramePadding        = ImVec2(8, 6);
    style.ItemSpacing         = ImVec2(10, 8);
    style.WindowBorderSize    = 1.0f;
    style.FrameBorderSize     = 1.0f;
    style.PopupBorderSize     = 1.0f;
    style.WindowRounding      = 8.0f;
    style.FrameRounding       = 6.0f;
    style.ScrollbarRounding   = 12.0f;
    style.GrabRounding        = 6.0f;
    style.TabRounding         = 6.0f;
}

}
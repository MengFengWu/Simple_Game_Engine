#ifndef _WINDOW_EDITOR_CPP_
#define _WINDOW_EDITOR_CPP_

#include "window_editor.h"
#include "window.h"

#include "imgui.h"
#include "TextEditor.h"

#include <fstream>
#include <iostream>

Window_Editor::Window_Editor() : Window("Text Editor", 1080, 520, 100, 100)
{

}

Window_Editor::~Window_Editor()
{

}

bool Window_Editor::loadFile(const char* fileToEdit)
{
    if(mFileToEdit == NULL)
    {
        mFileToEdit = (char*)malloc((strlen(fileToEdit) + 1) * sizeof(char));
        strcpy(mFileToEdit, fileToEdit);
        std::cout << mFileToEdit << std::endl;
    }
    std::ifstream t;
    t.open(fileToEdit);
    if(t.good())
    {
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        editor.SetText(str);
    }
    return true;
}

bool Window_Editor::show()
{
    if(mVisible == false) return false;
    
    auto lang = TextEditor::LanguageDefinition::CPlusPlus();
    // set your own known preprocessor symbols...
	static const char* ppnames[] = { "NULL", "PM_REMOVE",
		"ZeroMemory", "DXGI_SWAP_EFFECT_DISCARD", "D3D_FEATURE_LEVEL", "D3D_DRIVER_TYPE_HARDWARE", "WINAPI","D3D11_SDK_VERSION", "assert" };
	// ... and their corresponding values
	static const char* ppvalues[] = { 
		"#define NULL ((void*)0)", 
		"#define PM_REMOVE (0x0001)",
		"Microsoft's own memory zapper function\n(which is a macro actually)\nvoid ZeroMemory(\n\t[in] PVOID  Destination,\n\t[in] SIZE_T Length\n); ", 
		"enum DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD = 0", 
		"enum D3D_FEATURE_LEVEL", 
		"enum D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE  = ( D3D_DRIVER_TYPE_UNKNOWN + 1 )",
		"#define WINAPI __stdcall",
		"#define D3D11_SDK_VERSION (7)",
		" #define assert(expression) (void)(                                                  \n"
        "    (!!(expression)) ||                                                              \n"
        "    (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \n"
        " )"
		};

	for (int i = 0; i < sizeof(ppnames) / sizeof(ppnames[0]); ++i)
	{
		TextEditor::Identifier id;
		id.mDeclaration = ppvalues[i];
		lang.mPreprocIdentifiers.insert(std::make_pair(std::string(ppnames[i]), id));
	}

	// set your own identifiers
	static const char* identifiers[] = {
		"HWND", "HRESULT", "LPRESULT","D3D11_RENDER_TARGET_VIEW_DESC", "DXGI_SWAP_CHAIN_DESC","MSG","LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
		"ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
		"ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
		"IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "TextEditor" };
	static const char* idecls[] = 
	{
		"typedef HWND_* HWND", "typedef long HRESULT", "typedef long* LPRESULT", "struct D3D11_RENDER_TARGET_VIEW_DESC", "struct DXGI_SWAP_CHAIN_DESC",
		"typedef tagMSG MSG\n * Message structure","typedef LONG_PTR LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
		"ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
		"ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
		"IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "class TextEditor" };
	for (int i = 0; i < sizeof(identifiers) / sizeof(identifiers[0]); ++i)
	{
		TextEditor::Identifier id;
		id.mDeclaration = std::string(idecls[i]);
		lang.mIdentifiers.insert(std::make_pair(std::string(identifiers[i]), id));
	}
	editor.SetLanguageDefinition(lang);
	//editor.SetPalette(TextEditor::GetLightPalette());

	// error markers
	TextEditor::ErrorMarkers markers;
	markers.insert(std::make_pair<int, std::string>(6, "Example error here:\nInclude file not found: \"TextEditor.h\""));
	markers.insert(std::make_pair<int, std::string>(41, "Another example error"));
	editor.SetErrorMarkers(markers);

	// "breakpoint" markers
	//TextEditor::Breakpoints bpts;
	//bpts.insert(24);
	//bpts.insert(47);
	//editor.SetBreakpoints(bpts);
    
    auto cpos = editor.GetCursorPosition();
    //ImGui::SetNextWindowPos(mPos, ImGuiCond_Always);
    //ImGui::SetNextWindowSize(mSize, ImGuiCond_Always);

    ImGui::Begin(mName, nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
    if(ImGui::BeginMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Save"))
            {
                auto textToSave = editor.GetText();
                
                std::ofstream outFile(mFileToEdit, std::ios::trunc);
                if(outFile.is_open())
                {
                    outFile << textToSave;
                }
                else
                {
                    //TO-DO: error message
                }
            }
            if(ImGui::MenuItem("Quit", "Alt-F4"))
            {
                mVisible = false;
            }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Edit"))
        {
            bool ro = editor.IsReadOnly();
            if(ImGui::MenuItem("Read-only mode", nullptr, &ro))
                editor.SetReadOnly(ro);
            ImGui::Separator();

            if(ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
                editor.Undo();
            if(ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
                editor.Redo();

            ImGui::Separator();

            if(ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
                editor.Copy();
            if(ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
                editor.Cut();
            if(ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
                editor.Delete();
            if(ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                editor.Paste();

            ImGui::Separator();

            if(ImGui::MenuItem("Select all", nullptr, nullptr))
                editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("View"))
        {
            if(ImGui::MenuItem("Dark palette"))
                editor.SetPalette(TextEditor::GetDarkPalette());
            if(ImGui::MenuItem("Light palette"))
                editor.SetPalette(TextEditor::GetLightPalette());
            if(ImGui::MenuItem("Retro blue palette"))
                editor.SetPalette(TextEditor::GetRetroBluePalette());
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();   
    }

    ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
                editor.IsOverwrite() ? "Ovr" : "Ins",
                editor.CanUndo() ? "*" : " ",
                editor.GetLanguageDefinition().mName.c_str(), mFileToEdit);

    editor.Render("TextEditor");
    ImGui::End();
    return true;
}

#endif //_WINDOW_EDITOR_CPP_
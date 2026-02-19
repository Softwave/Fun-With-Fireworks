// Fun with fireworks
// (c) Softwave 2026 https://s0ftwave.net/
// MIT License 

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "rlImGui.h"
#include "imgui.h"
#include <vector>
#include <cmath>
#include <random>

void SetupImGuiStyle()
{
	// S0ftwave style from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();
	
	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 0.0f;
	style.TabBorderSize = 0.0f;
	//style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
	
	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 0.99999f, 0.99999f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.7529412f, 0.7529412f, 0.72156864f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.48235294f, 0.5647059f, 0.70980394f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.16078432f, 0.3372549f, 0.3764706f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.40784314f, 0.4745098f, 0.627451f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.49803922f, 0.49803922f, 0.49803922f, 0.5f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.29411766f, 0.3372549f, 0.5019608f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24313726f, 0.24313726f, 0.40392157f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.60784316f, 0.5568628f, 0.76862746f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.29411766f, 0.3372549f, 0.5019608f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.29411766f, 0.3372549f, 0.5019608f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.60784316f, 0.5568628f, 0.76862746f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.4f, 0.4f, 0.54901963f, 0.8f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.40784314f, 0.4745098f, 0.627451f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.60784316f, 0.5568628f, 0.76862746f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.74714285f, 0.70644146f, 0.8755365f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5597157f, 0.52762073f, 0.6609442f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.99999f, 0.9999946f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.60784316f, 0.5568628f, 0.76862746f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.29411766f, 0.3372549f, 0.5019608f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.29411766f, 0.3372549f, 0.5019608f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4f, 0.47843137f, 0.70980394f, 0.79f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.16078432f, 0.3372549f, 0.3764706f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.40784314f, 0.4745098f, 0.627451f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.08627451f, 0.2627451f, 0.3019608f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.16078432f, 0.3372549f, 0.3764706f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.49803922f, 0.49803922f, 0.49803922f, 0.6f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.6f, 0.6f, 0.69803923f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.69803923f, 0.69803923f, 0.8980392f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.0f, 1.0f, 1.0f, 0.1f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.7764706f, 0.81960785f, 1.0f, 0.6f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.7764706f, 0.81960785f, 1.0f, 0.9f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.29411766f, 0.3372549f, 0.5019608f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.60784316f, 0.5568628f, 0.76862746f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.18431373f, 0.21568628f, 0.32156864f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.28235295f, 0.28235295f, 0.5686275f, 0.8212f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.34901962f, 0.34901962f, 0.6509804f, 0.8372f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.9607843f, 0.5529412f, 0.7647059f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.60784316f, 0.5568628f, 0.76862746f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.9607843f, 0.5529412f, 0.7647059f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.24550092f, 0.29866496f, 0.42060083f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.30980393f, 0.30980393f, 0.44705883f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.25882354f, 0.25882354f, 0.2784314f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.07f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.0f, 1.0f, 0.35f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.9f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.44705883f, 0.44705883f, 0.8980392f, 0.8f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.2f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.2f, 0.2f, 0.2f, 0.35f);

    style.Colors[ImGuiCol_TextLink] = ImVec4(0.78888888888f, 0.73111f, 0.97111f, 1.0f);
}

bool showMessageBox = false;
static bool editMinParticles = false;
static bool editMaxParticles = false;

struct Particle
{
    Vector2 position;
    Vector2 velocity;
    Color color;
    float lifetime;
    float maxLifetime;
    float size;
    float angle;
    float spin;
    float initialAngle;
    Vector2 spawnPosition;
    float baseHue;
    std::vector<Vector2> trail;
    float initialSize;
};

class PsychedelicParticleSystem
{
public:
    int minParticles = 700;
    int maxParticles = 2000;
    float minSpeed = 100.0f;
    float maxSpeed = 400.0f;
    float minLifetime = 1.5f;
    float maxLifetime = 3.5f;
    float minSize = 3.0f;
    float maxSize = 14.0f;
    float gravity = 200.0f;
    float airResistance = 0.995f;
    float glowIntensity = 4.5f;
    float glowSize = 12.8f;
    float colorVariation = 60.0f;
    float angleRandomness = 0.5f;
    float spinMultiplier = 15.0f;
    float trailModLength = 0.08f;
    float tailModX = 0.03f;
    float tailModY = 0.03f;
    float hueModX = 20.0f;
    float hueModY = 360.0f;
    float trailLengthLimit = 20.0f;

    
private:
    std::vector<Particle> particles;
    std::mt19937 rng;
    std::uniform_real_distribution<float> randFloat;
    float time;
    Shader glowShader;
    Texture2D particleTexture;
    RenderTexture2D glowBuffer;
    Font customFont;
    
public:
    PsychedelicParticleSystem() : randFloat(0.0f, 1.0f), time(0.0f)
    {
        rng.seed(std::random_device{}());
        particles.reserve(12000);
    }
    
    void InitializeShaders(int screenWidth, int screenHeight)
    {
        glowShader = LoadShader("glow.vs", "glow.fs");
        customFont = LoadFont("editundo.ttf");
        
        Image img = GenImageColor(64, 64, BLANK);
        for (int y = 0; y < 64; y++)
        {
            for (int x = 0; x < 64; x++)
            {
                float dx = x - 32.0f;
                float dy = y - 32.0f;
                float distance = sqrtf(dx*dx + dy*dy) / 32.0f;
                if (distance <= 1.0f)
                {
                    Color pixelColor = WHITE;
                    pixelColor.a = (unsigned char)(255 * (1.0f - distance));
                    ImageDrawPixel(&img, x, y, pixelColor);
                }
            }
        }
        particleTexture = LoadTextureFromImage(img);
        UnloadImage(img);
        
        glowBuffer = LoadRenderTexture(screenWidth, screenHeight);
    }
    
    void UnloadResources()
    {
        UnloadShader(glowShader);
        UnloadTexture(particleTexture);
        UnloadRenderTexture(glowBuffer);
        UnloadFont(customFont);
    }
    
    Font GetFont() const
    {
        return customFont;
    }
    
    void SpawnFirework(Vector2 position)
    {
        int particleCount = minParticles + rand() % (maxParticles - minParticles);
        float baseHue = randFloat(rng) * 360;
        
        for (int i = 0; i < particleCount; i++)
        {
            Particle p;
            p.position = position;
            
            float angle = (2 * PI * i / particleCount) + (randFloat(rng) - 0.5f) * angleRandomness;
            float speed = randFloat(rng) * (maxSpeed - minSpeed) + minSpeed;
            p.velocity = {cosf(angle) * speed, sinf(angle) * speed};
            

            p.spawnPosition = position;
            p.baseHue = baseHue;

            p.maxLifetime = randFloat(rng) * (maxLifetime - minLifetime) + minLifetime;
            p.lifetime = p.maxLifetime;
            p.size = randFloat(rng) * (maxSize - minSize) + minSize;
            p.angle = angle;
            p.spin = (randFloat(rng) - 0.5f) * spinMultiplier;
            
            float hue = fmodf(baseHue + (randFloat(rng) - 0.5f) * colorVariation, 360);
            p.color = ColorFromHSV(hue, 0.9f, 1.0f);
            //p.color = ColorContrast(p.color, 0.7f); // increase contrast for better visibility
            
            p.initialSize = p.size;

            particles.push_back(p);
        }
    }
    
    void Update(float deltaTime)
    {
        time += deltaTime;
        
        for (auto it = particles.begin(); it != particles.end();)
        {
            it->lifetime -= deltaTime;
            
            if (it->lifetime <= 0)
            {
                it = particles.erase(it);
                continue;
            }
            
            float lifeRatio = it->lifetime / it->maxLifetime;
            
            // Update pos
            it->position.x += it->velocity.x * deltaTime;
            it->position.y += it->velocity.y * deltaTime;

            // Trail
            it->trail.push_back(it->position);
            if (it->trail.size() > trailLengthLimit) // Trail length limit 
                it->trail.erase(it->trail.begin());
            
            it->velocity.x *= airResistance;
            it->velocity.y *= airResistance;
            it->velocity.y += gravity * deltaTime;
            
            it->angle += it->spin * deltaTime;
            
            float dx = it->position.x - it->spawnPosition.x;
            float dy = it->position.y - it->spawnPosition.y;
            float dist = sqrtf(dx*dx + dy*dy);
            float hue = fmodf(it->baseHue + dist * 0.4f, 360); // hue changes based on distance from spawn, multiplied by 0.4 to control how fast it changes
            float saturation = 0.7f + sinf(time * 3) * 0.3f; // default is time * 3, but it can be changed to be more strobe-y
            float brightness = lifeRatio * (0.8f + sinf(time * 12 + it->angle) * 0.2f);
            it->color = ColorFromHSV(hue, saturation, brightness);
            
            it->size = (2 + sinf(time * 5 + it->angle) * 1) * lifeRatio;

            ++it;
        }
    }
    
    void Draw()
    {
        BeginTextureMode(glowBuffer);
        ClearBackground(BLANK);
        BeginBlendMode(BLEND_ADDITIVE);
        BeginShaderMode(glowShader);
        
        SetShaderValue(glowShader, GetShaderLocation(glowShader, "glowIntensity"), &glowIntensity, SHADER_UNIFORM_FLOAT);
        SetShaderValue(glowShader, GetShaderLocation(glowShader, "glowSize"), &glowSize, SHADER_UNIFORM_FLOAT);
        
        for (const auto& p : particles)
        {
            float alpha = p.lifetime / p.maxLifetime;
            Color drawColor = p.color;
            drawColor.a = (unsigned char)(255 * alpha);
            
            Rectangle source = {0, 0, (float)particleTexture.width, (float)particleTexture.height};
            Rectangle dest = {p.position.x - p.size, p.position.y - p.size, p.size * 2, p.size * 2};
            Vector2 origin = {p.size, p.size};
            DrawTexturePro(particleTexture, source, dest, origin, p.angle * RAD2DEG, drawColor);
            
            Vector2 tailPos = 
            {
                p.position.x - p.velocity.x * tailModX,
                p.position.y - p.velocity.y * tailModY
            };
            Color tailColor = drawColor;
            tailColor.a = (unsigned char)(127 * alpha);
            Rectangle tailDest = {tailPos.x - p.size * 0.7f, tailPos.y - p.size * 0.7f, p.size * 1.4f, p.size * 1.4f};
            Vector2 tailOrigin = {p.size * 0.7f, p.size * 0.7f};
            DrawTexturePro(particleTexture, source, tailDest, tailOrigin, p.angle * RAD2DEG, tailColor);
        
            // Draw trail, it took me forever to get these right 
            for (int t = 0; t < (int)p.trail.size(); t++)
            {
                float trailRatio = (float)t / p.trail.size();
                float trailAlpha = alpha * trailRatio * 0.6f;
                Color trailColor = drawColor;
                trailColor.a = (unsigned char)(255 * trailAlpha);
                float trailSize = p.size * trailRatio * trailModLength;
                Rectangle trailDest = {p.trail[t].x - trailSize, p.trail[t].y - trailSize, trailSize * 2, trailSize * 2};
                Vector2 trailOrigin = {trailSize, trailSize};
                DrawTexturePro(particleTexture, source, trailDest, trailOrigin, p.angle * RAD2DEG, trailColor);
            }
        }

        EndShaderMode();
        EndBlendMode();
        EndTextureMode();

        // Draw the glow over everything yo 
        BeginBlendMode(BLEND_ADDITIVE);
        DrawTextureRec(glowBuffer.texture, {0, 0, (float)glowBuffer.texture.width, -(float)glowBuffer.texture.height}, {0, 0}, WHITE);
        EndBlendMode();
    }
    
    size_t GetParticleCount() const
    {
        return particles.size();
    }
};

int main(void) 
{
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Fun W. Fireworks");
    rlImGuiSetup(true);
    SetupImGuiStyle();
    SetTargetFPS(60);

    InitAudioDevice();
    Sound boomWav = LoadSound("firework.wav");
    
    PsychedelicParticleSystem particleSystem;
    particleSystem.InitializeShaders(screenWidth, screenHeight);

    // Auto-load settings at startup if the default settings file exists in same dir
    static char settingsFile[128] = "fireworks_settings.ini";
    FILE* f = fopen(settingsFile, "r");
    if (f) {
        fscanf(f, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
            &particleSystem.minParticles,
            &particleSystem.maxParticles,
            &particleSystem.minSpeed,
            &particleSystem.maxSpeed,
            &particleSystem.minLifetime,
            &particleSystem.maxLifetime,
            &particleSystem.minSize,
            &particleSystem.maxSize,
            &particleSystem.gravity,
            &particleSystem.airResistance,
            &particleSystem.glowIntensity,
            &particleSystem.glowSize,
            &particleSystem.colorVariation,
            &particleSystem.angleRandomness,
            &particleSystem.spinMultiplier,
            &particleSystem.trailModLength,
            &particleSystem.hueModX,
            &particleSystem.hueModY,
            &particleSystem.trailLengthLimit
        );
        fclose(f);
    }
    
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        
        particleSystem.Update(deltaTime);
        
        BeginDrawing();
        
        float time = GetTime();
        float bgHue = fmodf(time * particleSystem.hueModX, particleSystem.hueModY);
        Color bgColor = ColorFromHSV(bgHue, 0.3f, 0.1f);
        ClearBackground(bgColor);
        
        particleSystem.Draw();
        
        DrawTextEx(particleSystem.GetFont(), TextFormat("Particles: %d", (int)particleSystem.GetParticleCount()), {10, 10}, 20, 2, WHITE);
        DrawTextEx(particleSystem.GetFont(), "CLICK LEFT MOUSE to launch firework", {10, 40}, 20, 2, WHITE);
        
        // The actual ImGui window and controls
        rlImGuiBegin();
        // Set window size
        ImGui::SetNextWindowSize(ImVec2(408, 472), ImGuiCond_Once);
        ImGui::Begin("Firework Controls");
        ImGui::SliderInt("Min Particles", &particleSystem.minParticles, 1, 5000);
        ImGui::SliderInt("Max Particles", &particleSystem.maxParticles, 1, 8000);
        ImGui::SliderFloat("Min Speed", &particleSystem.minSpeed, 0.0f, 1000.0f);
        ImGui::SliderFloat("Max Speed", &particleSystem.maxSpeed, 0.0f, 1000.0f);
        ImGui::SliderFloat("Min Lifetime", &particleSystem.minLifetime, 0.1f, 10.0f);
        ImGui::SliderFloat("Max Lifetime", &particleSystem.maxLifetime, 0.1f, 10.0f);
        
        //if (ImGui::SliderFloat("Min Size", &particleSystem.minSize, 0.1f, 50.0f))
        //    particleSystem.minSize = roundf(particleSystem.minSize * 10.0f) / 10.0f;
        //if (ImGui::SliderFloat("Max Size", &particleSystem.maxSize, 0.1f, 50.0f))
        //    particleSystem.maxSize = roundf(particleSystem.maxSize * 10.0f) / 10.0f;
        ImGui::SliderFloat("Gravity", &particleSystem.gravity, -1000.0f, 1000.0f);
        ImGui::SliderFloat("Air Resistance", &particleSystem.airResistance, 0.90f, 1.0f);
        ImGui::SliderFloat("Glow Intensity", &particleSystem.glowIntensity, 0.0f, 20.0f);
        ImGui::SliderFloat("Glow Size", &particleSystem.glowSize, 0.0f, 50.0f);
        //ImGui::SliderFloat("Colour Variation", &particleSystem.colorVariation, 0.0f, 360.0f);
        ImGui::SliderFloat("Angle Randomness", &particleSystem.angleRandomness, 0.0f, 2.0f);
        ImGui::SliderFloat("Spin Multiplier", &particleSystem.spinMultiplier, 0.0f, 50.0f);
        if (ImGui::SliderFloat("Trail Mod Length", &particleSystem.trailModLength, 0.0f, 2.0f))
            particleSystem.trailModLength = roundf(particleSystem.trailModLength * 100.0f) / 100.0f;

        ImGui::SliderFloat("Trail Length Limit", &particleSystem.trailLengthLimit, 0.0f, 100.0f);

        //ImGui::SliderFloat("Tail Mod X", &particleSystem.tailModX, 0.0f, 0.5f);
        //ImGui::SliderFloat("Tail Mod Y", &particleSystem.tailModY, 0.0f, 0.5f);
        ImGui::SliderFloat("BG Hue Mod X", &particleSystem.hueModX, 0.0f, 100.0f);
        ImGui::SliderFloat("BG Hue Mod Y", &particleSystem.hueModY, 1.0f, 3600.0f);

        static char settingsFile[128] = "fireworks_settings.ini";
        if (ImGui::Button("Save Settings")) {
            FILE* f = fopen(settingsFile, "w");
            if (f) {
                fprintf(f, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
                    particleSystem.minParticles,
                    particleSystem.maxParticles,
                    particleSystem.minSpeed,
                    particleSystem.maxSpeed,
                    particleSystem.minLifetime,
                    particleSystem.maxLifetime,
                    particleSystem.minSize,
                    particleSystem.maxSize,
                    particleSystem.gravity,
                    particleSystem.airResistance,
                    particleSystem.glowIntensity,
                    particleSystem.glowSize,
                    particleSystem.colorVariation,
                    particleSystem.angleRandomness,
                    particleSystem.spinMultiplier,
                    particleSystem.trailModLength,
                    particleSystem.hueModX,
                    particleSystem.hueModY,
                    particleSystem.trailLengthLimit
                );
                fclose(f);
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Load Settings")) {
            FILE* f = fopen(settingsFile, "r");
            if (f) {
                fscanf(f, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
                    &particleSystem.minParticles,
                    &particleSystem.maxParticles,
                    &particleSystem.minSpeed,
                    &particleSystem.maxSpeed,
                    &particleSystem.minLifetime,
                    &particleSystem.maxLifetime,
                    &particleSystem.minSize,
                    &particleSystem.maxSize,
                    &particleSystem.gravity,
                    &particleSystem.airResistance,
                    &particleSystem.glowIntensity,
                    &particleSystem.glowSize,
                    &particleSystem.colorVariation,
                    &particleSystem.angleRandomness,
                    &particleSystem.spinMultiplier,
                    &particleSystem.trailModLength,
                    &particleSystem.hueModX,
                    &particleSystem.hueModY,
                    &particleSystem.trailLengthLimit
                );
                fclose(f);
            }
        }
        
        // Actually load and save settings
        ImGui::InputText("Settings File", settingsFile, sizeof(settingsFile));
        // About and Quit buttons 
        static bool showAbout = false;
        if (ImGui::Button("About")) showAbout = true;
        if (showAbout) {
            ImGui::OpenPopup("About");
        }
        if (ImGui::BeginPopupModal("About", &showAbout, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Fun W. Fireworks\n© Softwave 2026\n");
            ImGui::TextLinkOpenURL("https://s0ftwave.net/");
            ImGui::Separator();
            ImGui::Text("Made with C++, Raylib, and ImGui\nMIT License");
            ImGui::Text("Check out my YouTube channel for more code fun.\n");
            ImGui::TextLinkOpenURL("https://www.youtube.com/@softwave1662");
            if (ImGui::Button("OK")) {
                showAbout = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::SameLine();
        ImGui::Button("Quit");
        if (ImGui::IsItemClicked()) {
            goto endLabel; // I felt cheeky and like using a goto, ha 
        }
        
        ImGui::End();
        rlImGuiEnd();

        // Don't make fireworks if the mouse is over the ui
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!ImGui::GetIO().WantCaptureMouse) {
                Vector2 mousePos = GetMousePosition();
                particleSystem.SpawnFirework(mousePos);
                PlaySound(boomWav);
            }
        }

        EndDrawing();
    }
    
    endLabel:
    UnloadSound(boomWav);
    particleSystem.UnloadResources();
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
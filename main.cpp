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

// Version number
const char* VERSION = "0.3";

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

int MAX_TRAIL_POINTS = 8000;

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
    int trailHead;
    int trailCount;
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
    float bloomStrength = 1.2f;
    float bloomThreshold = 0.65f;
    float bloomResolutionScale = 0.5f;
    int bloomBlurPasses = 4;
    float colorVariation = 60.0f;
    float trailModLength = 0.08f;
    float tailModX = 0.03f;
    float tailModY = 0.03f;
    float hueModX = 20.0f;
    float hueModY = 360.0f;
    float trailLengthLimit = 20.0f;
    float glowResolutionScale = 1.0f;

    
private:
    std::vector<Particle> particles;
    std::mt19937 rng;
    std::uniform_real_distribution<float> randFloat;
    float time;
    Shader glowShader;
    Shader bloomBrightShader;
    Shader bloomBlurShader;
    Texture2D particleTexture;
    RenderTexture2D glowBuffer{};
    RenderTexture2D bloomPingBuffer{};
    RenderTexture2D bloomPongBuffer{};
    int glowBufferWidth = 0;
    int glowBufferHeight = 0;
    int bloomBufferWidth = 0;
    int bloomBufferHeight = 0;
    Font customFont;
    int glowIntensityLoc = -1;
    int glowSizeLoc = -1;
    int bloomThresholdLoc = -1;
    int bloomStrengthLoc = -1;
    int bloomBlurDirectionLoc = -1;
    static constexpr float fixedAngleRandomness = 0.5f;
    static constexpr float fixedSpinMultiplier = 15.0f;
    int activeTrailCapacity = 0;

    void SyncTrailCapacity()
    {
        if (MAX_TRAIL_POINTS < 1) MAX_TRAIL_POINTS = 1;
        if (MAX_TRAIL_POINTS > 20000) MAX_TRAIL_POINTS = 20000;
        if (MAX_TRAIL_POINTS == activeTrailCapacity) return;

        activeTrailCapacity = MAX_TRAIL_POINTS;
        for (auto& particle : particles)
        {
            particle.trail.assign(activeTrailCapacity, Vector2{0.0f, 0.0f});
            particle.trailHead = 0;
            particle.trailCount = 0;
        }
    }

    void RecreateGlowBuffer(int screenWidth, int screenHeight)
    {
        int targetWidth = (int)(screenWidth * glowResolutionScale);
        int targetHeight = (int)(screenHeight * glowResolutionScale);
        if (targetWidth < 1) targetWidth = 1;
        if (targetHeight < 1) targetHeight = 1;

        if (glowBuffer.id != 0) UnloadRenderTexture(glowBuffer);
        glowBuffer = LoadRenderTexture(targetWidth, targetHeight);
        SetTextureFilter(glowBuffer.texture, TEXTURE_FILTER_BILINEAR);
        glowBufferWidth = targetWidth;
        glowBufferHeight = targetHeight;
    }

    void RecreateBloomBuffers(int screenWidth, int screenHeight)
    {
        int targetWidth = (int)(screenWidth * bloomResolutionScale);
        int targetHeight = (int)(screenHeight * bloomResolutionScale);
        if (targetWidth < 1) targetWidth = 1;
        if (targetHeight < 1) targetHeight = 1;

        if (bloomPingBuffer.id != 0) UnloadRenderTexture(bloomPingBuffer);
        if (bloomPongBuffer.id != 0) UnloadRenderTexture(bloomPongBuffer);

        bloomPingBuffer = LoadRenderTexture(targetWidth, targetHeight);
        bloomPongBuffer = LoadRenderTexture(targetWidth, targetHeight);
        SetTextureFilter(bloomPingBuffer.texture, TEXTURE_FILTER_BILINEAR);
        SetTextureFilter(bloomPongBuffer.texture, TEXTURE_FILTER_BILINEAR);
        bloomBufferWidth = targetWidth;
        bloomBufferHeight = targetHeight;
    }

    void EnsureGlowBufferMatchesScreen()
    {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        int targetWidth = (int)(screenWidth * glowResolutionScale);
        int targetHeight = (int)(screenHeight * glowResolutionScale);
        if (targetWidth < 1) targetWidth = 1;
        if (targetHeight < 1) targetHeight = 1;

        if (targetWidth != glowBufferWidth || targetHeight != glowBufferHeight)
        {
            RecreateGlowBuffer(screenWidth, screenHeight);
        }
    }

    void EnsureBloomBuffersMatchScreen()
    {
        if (bloomResolutionScale < 0.125f) bloomResolutionScale = 0.125f;
        if (bloomResolutionScale > 1.0f) bloomResolutionScale = 1.0f;

        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        int targetWidth = (int)(screenWidth * bloomResolutionScale);
        int targetHeight = (int)(screenHeight * bloomResolutionScale);
        if (targetWidth < 1) targetWidth = 1;
        if (targetHeight < 1) targetHeight = 1;

        if (targetWidth != bloomBufferWidth || targetHeight != bloomBufferHeight)
        {
            RecreateBloomBuffers(screenWidth, screenHeight);
        }
    }
    
public:
    PsychedelicParticleSystem() : randFloat(0.0f, 1.0f), time(0.0f)
    {
        rng.seed(std::random_device{}());
        particles.reserve(12000);
        if (MAX_TRAIL_POINTS < 1) MAX_TRAIL_POINTS = 1;
        activeTrailCapacity = MAX_TRAIL_POINTS;
    }
    
    void InitializeShaders(int screenWidth, int screenHeight)
    {
        glowShader = LoadShader("glow.vs", "glow.fs");
        bloomBrightShader = LoadShader("glow.vs", "brightpass.fs");
        bloomBlurShader = LoadShader("glow.vs", "blur.fs");
        glowIntensityLoc = GetShaderLocation(glowShader, "glowIntensity");
        glowSizeLoc = GetShaderLocation(glowShader, "glowSize");
        bloomThresholdLoc = GetShaderLocation(bloomBrightShader, "threshold");
        bloomStrengthLoc = GetShaderLocation(bloomBrightShader, "strength");
        bloomBlurDirectionLoc = GetShaderLocation(bloomBlurShader, "direction");
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

        RecreateGlowBuffer(screenWidth, screenHeight);
        RecreateBloomBuffers(screenWidth, screenHeight);
    }
    
    void UnloadResources()
    {
        UnloadShader(glowShader);
        UnloadShader(bloomBrightShader);
        UnloadShader(bloomBlurShader);
        UnloadTexture(particleTexture);
        if (glowBuffer.id != 0) UnloadRenderTexture(glowBuffer);
        if (bloomPingBuffer.id != 0) UnloadRenderTexture(bloomPingBuffer);
        if (bloomPongBuffer.id != 0) UnloadRenderTexture(bloomPongBuffer);
        UnloadFont(customFont);
    }
    
    Font GetFont() const
    {
        return customFont;
    }
    
    void SpawnFirework(Vector2 position)
    {
        SyncTrailCapacity();

        int particleCount = minParticles + rand() % (maxParticles - minParticles);
        float baseHue = randFloat(rng) * 360;
        
        for (int i = 0; i < particleCount; i++)
        {
            Particle p{};
            p.position = position;
            
            float angle = (2 * PI * i / particleCount) + (randFloat(rng) - 0.5f) * fixedAngleRandomness;
            float speed = randFloat(rng) * (maxSpeed - minSpeed) + minSpeed;
            p.velocity = {cosf(angle) * speed, sinf(angle) * speed};
            

            p.spawnPosition = position;
            p.baseHue = baseHue;

            p.maxLifetime = randFloat(rng) * (maxLifetime - minLifetime) + minLifetime;
            p.lifetime = p.maxLifetime;
            p.size = randFloat(rng) * (maxSize - minSize) + minSize;
            p.angle = angle;
            p.spin = (randFloat(rng) - 0.5f) * fixedSpinMultiplier;
            
            float hue = fmodf(baseHue + (randFloat(rng) - 0.5f) * colorVariation, 360);
            p.color = ColorFromHSV(hue, 0.9f, 1.0f);
            //p.color = ColorContrast(p.color, 0.7f); // increase contrast for better visibility
            
            p.initialSize = p.size;
            p.trail.assign(activeTrailCapacity, Vector2{0.0f, 0.0f});
            p.trailHead = 0;
            p.trailCount = 0;

            particles.push_back(p);
        }
    }
    
    void Update(float deltaTime)
    {
        time += deltaTime;

        SyncTrailCapacity();

        int trailLimit = (int)trailLengthLimit;
        if (trailLimit < 0) trailLimit = 0;
        if (trailLimit > activeTrailCapacity) trailLimit = activeTrailCapacity;

        for (size_t i = 0; i < particles.size();)
        {
            Particle& particle = particles[i];
            particle.lifetime -= deltaTime;
            
            if (particle.lifetime <= 0)
            {
                particles[i] = particles.back();
                particles.pop_back();
                continue;
            }
            
            float lifeRatio = particle.lifetime / particle.maxLifetime;
            
            // Update pos
            particle.position.x += particle.velocity.x * deltaTime;
            particle.position.y += particle.velocity.y * deltaTime;

            // Trail
            if (trailLimit > 0 && !particle.trail.empty())
            {
                particle.trail[particle.trailHead] = particle.position;
                particle.trailHead = (particle.trailHead + 1) % activeTrailCapacity;
                if (particle.trailCount < trailLimit) particle.trailCount++;
            }
            else
            {
                particle.trailCount = 0;
            }
            
            particle.velocity.x *= airResistance;
            particle.velocity.y *= airResistance;
            particle.velocity.y += gravity * deltaTime;
            
            particle.angle += particle.spin * deltaTime;
            
            float dx = particle.position.x - particle.spawnPosition.x;
            float dy = particle.position.y - particle.spawnPosition.y;
            float dist = sqrtf(dx*dx + dy*dy);
            float hue = fmodf(particle.baseHue + dist * 0.4f, 360); // hue changes based on distance from spawn, multiplied by 0.4 to control how fast it changes
            float saturation = 0.7f + sinf(time * 3) * 0.3f; // default is time * 3, but it can be changed to be more strobe-y
            float brightness = lifeRatio * (0.8f + sinf(time * 12 + particle.angle) * 0.2f);
            particle.color = ColorFromHSV(hue, saturation, brightness);
            
            particle.size = (2 + sinf(time * 5 + particle.angle) * 1) * lifeRatio;

            ++i;
        }
    }
    
    void Draw()
    {
        SyncTrailCapacity();

        EnsureGlowBufferMatchesScreen();
        EnsureBloomBuffersMatchScreen();

        float screenWidth = (float)GetScreenWidth();
        float screenHeight = (float)GetScreenHeight();
        float glowScaleX = (float)glowBufferWidth / screenWidth;
        float glowScaleY = (float)glowBufferHeight / screenHeight;
        float glowDrawScale = (glowScaleX + glowScaleY) * 0.5f;

        int trailStep = 1;
        size_t particleCount = particles.size();
        if (particleCount > 9000) trailStep = 4;
        else if (particleCount > 6000) trailStep = 3;
        else if (particleCount > 3000) trailStep = 2;

        BeginTextureMode(glowBuffer);
        ClearBackground(BLANK);
        BeginBlendMode(BLEND_ADDITIVE);
        BeginShaderMode(glowShader);
        
        if (glowIntensityLoc >= 0) SetShaderValue(glowShader, glowIntensityLoc, &glowIntensity, SHADER_UNIFORM_FLOAT);
        if (glowSizeLoc >= 0) SetShaderValue(glowShader, glowSizeLoc, &glowSize, SHADER_UNIFORM_FLOAT);

        Rectangle source = {0, 0, (float)particleTexture.width, (float)particleTexture.height};
        
        for (const auto& p : particles)
        {
            float alpha = p.lifetime / p.maxLifetime;
            Color drawColor = p.color;
            drawColor.a = (unsigned char)(255 * alpha);
            
            float particleSize = p.size * glowDrawScale;
            float particleX = p.position.x * glowScaleX;
            float particleY = p.position.y * glowScaleY;

            Rectangle dest = {particleX - particleSize, particleY - particleSize, particleSize * 2, particleSize * 2};
            Vector2 origin = {particleSize, particleSize};
            DrawTexturePro(particleTexture, source, dest, origin, p.angle * RAD2DEG, drawColor);
            
            Vector2 tailPos = 
            {
                (p.position.x - p.velocity.x * tailModX) * glowScaleX,
                (p.position.y - p.velocity.y * tailModY) * glowScaleY
            };
            Color tailColor = drawColor;
            tailColor.a = (unsigned char)(127 * alpha);
            float tailSize = p.size * 0.7f * glowDrawScale;
            Rectangle tailDest = {tailPos.x - tailSize, tailPos.y - tailSize, tailSize * 2.0f, tailSize * 2.0f};
            Vector2 tailOrigin = {tailSize, tailSize};
            DrawTexturePro(particleTexture, source, tailDest, tailOrigin, p.angle * RAD2DEG, tailColor);
        
            // Draw trail, it took me forever to get these right 
            for (int t = 0; t < p.trailCount; t += trailStep)
            {
                int idx = (p.trailHead - p.trailCount + t + activeTrailCapacity) % activeTrailCapacity;
                float trailRatio = (float)(t + 1) / p.trailCount;
                float trailAlpha = alpha * trailRatio * 0.6f;
                Color trailColor = drawColor;
                trailColor.a = (unsigned char)(255 * trailAlpha);
                float trailSize = p.size * trailRatio * trailModLength * glowDrawScale;
                float trailX = p.trail[idx].x * glowScaleX;
                float trailY = p.trail[idx].y * glowScaleY;
                Rectangle trailDest = {trailX - trailSize, trailY - trailSize, trailSize * 2, trailSize * 2};
                Vector2 trailOrigin = {trailSize, trailSize};
                DrawTexturePro(particleTexture, source, trailDest, trailOrigin, p.angle * RAD2DEG, trailColor);
            }
        }

        EndShaderMode();
        EndBlendMode();
        EndTextureMode();

        if (bloomBlurPasses < 0) bloomBlurPasses = 0;

        if (bloomStrength > 0.0f && bloomBlurPasses > 0)
        {
            BeginTextureMode(bloomPingBuffer);
            ClearBackground(BLACK);
            BeginShaderMode(bloomBrightShader);
            if (bloomThresholdLoc >= 0) SetShaderValue(bloomBrightShader, bloomThresholdLoc, &bloomThreshold, SHADER_UNIFORM_FLOAT);
            if (bloomStrengthLoc >= 0) SetShaderValue(bloomBrightShader, bloomStrengthLoc, &bloomStrength, SHADER_UNIFORM_FLOAT);
            Rectangle glowSource = {0, 0, (float)glowBuffer.texture.width, -(float)glowBuffer.texture.height};
            Rectangle bloomDest = {0, 0, (float)bloomBufferWidth, (float)bloomBufferHeight};
            DrawTexturePro(glowBuffer.texture, glowSource, bloomDest, {0, 0}, 0.0f, WHITE);
            EndShaderMode();
            EndTextureMode();

            Vector2 blurDirH = {1.0f, 0.0f};
            Vector2 blurDirV = {0.0f, 1.0f};

            for (int pass = 0; pass < bloomBlurPasses; pass++)
            {
                BeginTextureMode(bloomPongBuffer);
                ClearBackground(BLACK);
                BeginShaderMode(bloomBlurShader);
                if (bloomBlurDirectionLoc >= 0) SetShaderValue(bloomBlurShader, bloomBlurDirectionLoc, &blurDirH, SHADER_UNIFORM_VEC2);
                Rectangle pingSource = {0, 0, (float)bloomPingBuffer.texture.width, -(float)bloomPingBuffer.texture.height};
                Rectangle pingDest = {0, 0, (float)bloomBufferWidth, (float)bloomBufferHeight};
                DrawTexturePro(bloomPingBuffer.texture, pingSource, pingDest, {0, 0}, 0.0f, WHITE);
                EndShaderMode();
                EndTextureMode();

                BeginTextureMode(bloomPingBuffer);
                ClearBackground(BLACK);
                BeginShaderMode(bloomBlurShader);
                if (bloomBlurDirectionLoc >= 0) SetShaderValue(bloomBlurShader, bloomBlurDirectionLoc, &blurDirV, SHADER_UNIFORM_VEC2);
                Rectangle pongSource = {0, 0, (float)bloomPongBuffer.texture.width, -(float)bloomPongBuffer.texture.height};
                Rectangle pongDest = {0, 0, (float)bloomBufferWidth, (float)bloomBufferHeight};
                DrawTexturePro(bloomPongBuffer.texture, pongSource, pongDest, {0, 0}, 0.0f, WHITE);
                EndShaderMode();
                EndTextureMode();
            }
        }

        // Draw the glow over everything yo 
        BeginBlendMode(BLEND_ADDITIVE);
        Rectangle glowSource = {0, 0, (float)glowBuffer.texture.width, -(float)glowBuffer.texture.height};
        Rectangle glowDest = {0, 0, screenWidth, screenHeight};
        DrawTexturePro(glowBuffer.texture, glowSource, glowDest, {0, 0}, 0.0f, WHITE);

        if (bloomStrength > 0.0f && bloomBlurPasses > 0)
        {
            Rectangle bloomSource = {0, 0, (float)bloomPingBuffer.texture.width, -(float)bloomPingBuffer.texture.height};
            Rectangle bloomDest = {0, 0, screenWidth, screenHeight};
            DrawTexturePro(bloomPingBuffer.texture, bloomSource, bloomDest, {0, 0}, 0.0f, WHITE);
        }
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
        char settingsLine[512] = {0};
        if (fgets(settingsLine, sizeof(settingsLine), f)) {
            float oldAngleRandomness;
            float oldSpinMultiplier;
            int loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %f %f %f %d",
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
                &oldAngleRandomness,
                &oldSpinMultiplier,
                &particleSystem.trailModLength,
                &particleSystem.hueModX,
                &particleSystem.hueModY,
                &particleSystem.trailLengthLimit,
                &particleSystem.glowResolutionScale,
                &MAX_TRAIL_POINTS,
                &particleSystem.bloomStrength,
                &particleSystem.bloomThreshold,
                &particleSystem.bloomResolutionScale,
                &particleSystem.bloomBlurPasses
            );

            if (loaded != 25) {
                loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %f %f %f %d",
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
                    &particleSystem.trailModLength,
                    &particleSystem.hueModX,
                    &particleSystem.hueModY,
                    &particleSystem.trailLengthLimit,
                    &particleSystem.glowResolutionScale,
                    &MAX_TRAIL_POINTS,
                    &particleSystem.bloomStrength,
                    &particleSystem.bloomThreshold,
                    &particleSystem.bloomResolutionScale,
                    &particleSystem.bloomBlurPasses
                );
            }

            if (loaded != 25 && loaded != 23) {
                loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d",
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
                    &oldAngleRandomness,
                    &oldSpinMultiplier,
                    &particleSystem.trailModLength,
                    &particleSystem.hueModX,
                    &particleSystem.hueModY,
                    &particleSystem.trailLengthLimit,
                    &particleSystem.glowResolutionScale,
                    &MAX_TRAIL_POINTS
                );

                if (loaded != 21) {
                    loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d",
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
                        &particleSystem.trailModLength,
                        &particleSystem.hueModX,
                        &particleSystem.hueModY,
                        &particleSystem.trailLengthLimit,
                        &particleSystem.glowResolutionScale,
                        &MAX_TRAIL_POINTS
                    );
                }
            }

            if (loaded != 25 && loaded != 23 && loaded != 21 && loaded != 19) {
                loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
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
                    &oldAngleRandomness,
                    &oldSpinMultiplier,
                    &particleSystem.trailModLength,
                    &particleSystem.hueModX,
                    &particleSystem.hueModY,
                    &particleSystem.trailLengthLimit,
                    &particleSystem.glowResolutionScale
                );

                if (loaded != 20) {
                    loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
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
                        &particleSystem.trailModLength,
                        &particleSystem.hueModX,
                        &particleSystem.hueModY,
                        &particleSystem.trailLengthLimit,
                        &particleSystem.glowResolutionScale
                    );
                }
            }

            if (loaded < 18) particleSystem.glowResolutionScale = 1.0f;
            if (loaded < 23) {
                particleSystem.bloomStrength = 1.2f;
                particleSystem.bloomThreshold = 0.65f;
                particleSystem.bloomResolutionScale = 0.5f;
                particleSystem.bloomBlurPasses = 4;
            }
        }

        if (particleSystem.glowResolutionScale < 0.25f) particleSystem.glowResolutionScale = 0.25f;
        if (particleSystem.glowResolutionScale > 1.0f) particleSystem.glowResolutionScale = 1.0f;
        if (particleSystem.bloomStrength < 0.0f) particleSystem.bloomStrength = 0.0f;
        if (particleSystem.bloomStrength > 6.0f) particleSystem.bloomStrength = 6.0f;
        if (particleSystem.bloomThreshold < 0.0f) particleSystem.bloomThreshold = 0.0f;
        if (particleSystem.bloomThreshold > 1.5f) particleSystem.bloomThreshold = 1.5f;
        if (particleSystem.bloomResolutionScale < 0.125f) particleSystem.bloomResolutionScale = 0.125f;
        if (particleSystem.bloomResolutionScale > 1.0f) particleSystem.bloomResolutionScale = 1.0f;
        if (particleSystem.bloomBlurPasses < 0) particleSystem.bloomBlurPasses = 0;
        if (particleSystem.bloomBlurPasses > 8) particleSystem.bloomBlurPasses = 8;
        if (MAX_TRAIL_POINTS < 1) MAX_TRAIL_POINTS = 1;
        if (MAX_TRAIL_POINTS > 20000) MAX_TRAIL_POINTS = 20000;
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
        ImGui::SetNextWindowSize(ImVec2(408, 560), ImGuiCond_Once);
        ImGui::Begin("Firework Controls");
        ImGui::SliderInt("Min Particles", &particleSystem.minParticles, 1, 10000);
        ImGui::SliderInt("Max Particles", &particleSystem.maxParticles, 1, 11000);
        ImGui::SliderFloat("Min Speed", &particleSystem.minSpeed, 0.0f, 1000.0f);
        ImGui::SliderFloat("Max Speed", &particleSystem.maxSpeed, 0.0f, 1000.0f);
        ImGui::SliderFloat("Min Lifetime", &particleSystem.minLifetime, 0.1f, 10.0f);
        ImGui::SliderFloat("Max Lifetime", &particleSystem.maxLifetime, 0.1f,
                           10.0f);

        //if (ImGui::SliderFloat("Min Size", &particleSystem.minSize, 0.1f, 50.0f))
        //    particleSystem.minSize = roundf(particleSystem.minSize * 10.0f) / 10.0f;
        //if (ImGui::SliderFloat("Max Size", &particleSystem.maxSize, 0.1f, 50.0f))
        //    particleSystem.maxSize = roundf(particleSystem.maxSize * 10.0f) / 10.0f;
        ImGui::SliderFloat("Gravity", &particleSystem.gravity, -1000.0f, 1000.0f);
        ImGui::SliderFloat("Air Resistance", &particleSystem.airResistance, 0.90f, 1.0f);
        ImGui::SliderFloat("Glow Intensity", &particleSystem.glowIntensity, 0.0f, 10.0f);
        ImGui::SliderFloat("Glow Size", &particleSystem.glowSize, 0.0f, 1.0f);
        if (ImGui::SliderFloat("Glow Resolution Scale", &particleSystem.glowResolutionScale, 0.125f, 8.0f))
            particleSystem.glowResolutionScale = roundf(particleSystem.glowResolutionScale * 100.0f) / 100.0f;
        ImGui::SliderFloat("Bloom Strength", &particleSystem.bloomStrength, 0.0f, 6.0f);
        ImGui::SliderFloat("Bloom Threshold", &particleSystem.bloomThreshold, 0.0f, 1.5f);
        if (ImGui::SliderFloat("Bloom Resolution", &particleSystem.bloomResolutionScale, 0.125f, 1.0f))
            particleSystem.bloomResolutionScale = roundf(particleSystem.bloomResolutionScale * 100.0f) / 100.0f;
        ImGui::SliderInt("Bloom Blur Passes", &particleSystem.bloomBlurPasses, 0, 8);
        ImGui::SliderFloat("Color Variation", &particleSystem.colorVariation, 0.0f, 360.0f);
        if (ImGui::SliderFloat("Trail Thickness", &particleSystem.trailModLength, 0.0f, 2.0f))
            particleSystem.trailModLength = roundf(particleSystem.trailModLength * 100.0f) / 100.0f;

        ImGui::SliderFloat("Trail Length Limit", &particleSystem.trailLengthLimit, 0.0f, 1000.0f);
        ImGui::SliderInt("Max Trail Points", &MAX_TRAIL_POINTS, 1, 8000);

        //ImGui::SliderFloat("Tail Mod X", &particleSystem.tailModX, 0.0f, 0.5f);
        //ImGui::SliderFloat("Tail Mod Y", &particleSystem.tailModY, 0.0f, 0.5f);

        static char settingsFile[128] = "fireworks_settings.ini";
        if (ImGui::Button("Save Settings")) {
            FILE* f = fopen(settingsFile, "w");
            if (f) {
                fprintf(f, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %f %f %f %d\n",
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
                    particleSystem.trailModLength,
                    particleSystem.hueModX,
                    particleSystem.hueModY,
                    particleSystem.trailLengthLimit,
                    particleSystem.glowResolutionScale,
                    MAX_TRAIL_POINTS,
                    particleSystem.bloomStrength,
                    particleSystem.bloomThreshold,
                    particleSystem.bloomResolutionScale,
                    particleSystem.bloomBlurPasses
                );
                fclose(f);
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Load Settings")) {
            FILE* f = fopen(settingsFile, "r");
            if (f) {
                char settingsLine[512] = {0};
                if (fgets(settingsLine, sizeof(settingsLine), f)) {
                    float oldAngleRandomness;
                    float oldSpinMultiplier;
                    int loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %f %f %f %d",
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
                        &oldAngleRandomness,
                        &oldSpinMultiplier,
                        &particleSystem.trailModLength,
                        &particleSystem.hueModX,
                        &particleSystem.hueModY,
                        &particleSystem.trailLengthLimit,
                        &particleSystem.glowResolutionScale,
                        &MAX_TRAIL_POINTS,
                        &particleSystem.bloomStrength,
                        &particleSystem.bloomThreshold,
                        &particleSystem.bloomResolutionScale,
                        &particleSystem.bloomBlurPasses
                    );

                    if (loaded != 25) {
                        loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %f %f %f %d",
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
                            &particleSystem.trailModLength,
                            &particleSystem.hueModX,
                            &particleSystem.hueModY,
                            &particleSystem.trailLengthLimit,
                            &particleSystem.glowResolutionScale,
                            &MAX_TRAIL_POINTS,
                            &particleSystem.bloomStrength,
                            &particleSystem.bloomThreshold,
                            &particleSystem.bloomResolutionScale,
                            &particleSystem.bloomBlurPasses
                        );
                    }

                    if (loaded != 25 && loaded != 23) {
                        loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d",
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
                            &oldAngleRandomness,
                            &oldSpinMultiplier,
                            &particleSystem.trailModLength,
                            &particleSystem.hueModX,
                            &particleSystem.hueModY,
                            &particleSystem.trailLengthLimit,
                            &particleSystem.glowResolutionScale,
                            &MAX_TRAIL_POINTS
                        );

                        if (loaded != 21) {
                            loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d",
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
                                &particleSystem.trailModLength,
                                &particleSystem.hueModX,
                                &particleSystem.hueModY,
                                &particleSystem.trailLengthLimit,
                                &particleSystem.glowResolutionScale,
                                &MAX_TRAIL_POINTS
                            );
                        }
                    }

                    if (loaded != 25 && loaded != 23 && loaded != 21 && loaded != 19) {
                        loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
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
                            &oldAngleRandomness,
                            &oldSpinMultiplier,
                            &particleSystem.trailModLength,
                            &particleSystem.hueModX,
                            &particleSystem.hueModY,
                            &particleSystem.trailLengthLimit,
                            &particleSystem.glowResolutionScale
                        );

                        if (loaded != 20) {
                            loaded = sscanf(settingsLine, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
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
                                &particleSystem.trailModLength,
                                &particleSystem.hueModX,
                                &particleSystem.hueModY,
                                &particleSystem.trailLengthLimit,
                                &particleSystem.glowResolutionScale
                            );
                        }
                    }

                    if (loaded < 18) particleSystem.glowResolutionScale = 1.0f;
                    if (loaded < 23) {
                        particleSystem.bloomStrength = 1.2f;
                        particleSystem.bloomThreshold = 0.65f;
                        particleSystem.bloomResolutionScale = 0.5f;
                        particleSystem.bloomBlurPasses = 4;
                    }
                }

                if (particleSystem.glowResolutionScale < 0.25f) particleSystem.glowResolutionScale = 0.25f;
                if (particleSystem.glowResolutionScale > 1.0f) particleSystem.glowResolutionScale = 1.0f;
                if (particleSystem.bloomStrength < 0.0f) particleSystem.bloomStrength = 0.0f;
                if (particleSystem.bloomStrength > 6.0f) particleSystem.bloomStrength = 6.0f;
                if (particleSystem.bloomThreshold < 0.0f) particleSystem.bloomThreshold = 0.0f;
                if (particleSystem.bloomThreshold > 1.5f) particleSystem.bloomThreshold = 1.5f;
                if (particleSystem.bloomResolutionScale < 0.125f) particleSystem.bloomResolutionScale = 0.125f;
                if (particleSystem.bloomResolutionScale > 1.0f) particleSystem.bloomResolutionScale = 1.0f;
                if (particleSystem.bloomBlurPasses < 0) particleSystem.bloomBlurPasses = 0;
                if (particleSystem.bloomBlurPasses > 8) particleSystem.bloomBlurPasses = 8;
                if (MAX_TRAIL_POINTS < 1) MAX_TRAIL_POINTS = 1;
                if (MAX_TRAIL_POINTS > 20000) MAX_TRAIL_POINTS = 20000;
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
            ImGui::Text("Fun W. Fireworks %s\n© Softwave 2026\n", VERSION);
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

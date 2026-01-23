// Fun with fireworks
// (c) Softwave 2026 https://s0ftwave.net/
// MIT License 

#include "raylib.h"
#include <vector>
#include <cmath>
#include <random>

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
};

class PsychedelicParticleSystem
{
public:
    int minParticles = 700;
    int maxParticles = 1000;
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
            
            p.maxLifetime = randFloat(rng) * (maxLifetime - minLifetime) + minLifetime;
            p.lifetime = p.maxLifetime;
            p.size = randFloat(rng) * (maxSize - minSize) + minSize;
            p.angle = angle;
            p.spin = (randFloat(rng) - 0.5f) * spinMultiplier;
            
            float hue = fmodf(baseHue + (randFloat(rng) - 0.5f) * colorVariation, 360);
            p.color = ColorFromHSV(hue, 0.9f, 1.0f);
            
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
            
            it->position.x += it->velocity.x * deltaTime;
            it->position.y += it->velocity.y * deltaTime;
            
            it->velocity.x *= airResistance;
            it->velocity.y *= airResistance;
            it->velocity.y += gravity * deltaTime;
            
            it->angle += it->spin * deltaTime;
            
            float hue = fmodf(time * 100 + it->position.x * 0.5f + it->position.y * 0.3f, 360);
            float saturation = 0.7f + sinf(time * 3) * 0.3f;
            float brightness = lifeRatio * (0.8f + sinf(time * 7 + it->angle) * 0.2f);
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
                p.position.x - p.velocity.x * 0.02f,
                p.position.y - p.velocity.y * 0.02f
            };
            Color tailColor = drawColor;
            tailColor.a = (unsigned char)(127 * alpha);
            Rectangle tailDest = {tailPos.x - p.size * 0.7f, tailPos.y - p.size * 0.7f, p.size * 1.4f, p.size * 1.4f};
            Vector2 tailOrigin = {p.size * 0.7f, p.size * 0.7f};
            DrawTexturePro(particleTexture, source, tailDest, tailOrigin, p.angle * RAD2DEG, tailColor);
        }
        
        EndShaderMode();
        EndBlendMode();
        EndTextureMode();
        
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
    const int screenWidth = 1200;
    const int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Fun W Fireworks");
    SetTargetFPS(60);

    InitAudioDevice();
    Sound boomWav = LoadSound("firework.wav");
    
    PsychedelicParticleSystem particleSystem;
    particleSystem.InitializeShaders(screenWidth, screenHeight);
    
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos = GetMousePosition();
            particleSystem.SpawnFirework(mousePos);
            PlaySound(boomWav);
        }
        
        if (IsKeyPressed(KEY_SPACE))
        {
            Vector2 randomPos = {
                (float)(rand() % screenWidth),
                (float)(rand() % screenHeight)
            };
            particleSystem.SpawnFirework(randomPos);
            PlaySound(boomWav);
        }
        
        particleSystem.Update(deltaTime);
        
        BeginDrawing();
        
        float time = GetTime();
        float bgHue = fmodf(time * 20, 360);
        Color bgColor = ColorFromHSV(bgHue, 0.3f, 0.1f);
        ClearBackground(bgColor);
        
        particleSystem.Draw();
        
        DrawTextEx(particleSystem.GetFont(), TextFormat("Particles: %d", (int)particleSystem.GetParticleCount()), {10, 10}, 20, 2, WHITE);
        DrawTextEx(particleSystem.GetFont(), "CLICK LEFT MOUSE to launch firework", {10, 40}, 20, 2, WHITE);
        
        EndDrawing();
    }
    
    UnloadSound(boomWav);
    particleSystem.UnloadResources();
    CloseWindow();
    return 0;
}
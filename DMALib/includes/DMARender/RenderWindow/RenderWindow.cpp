#include "RenderWindow.h"
//#include <iostream>

ImVec2 g_mainPlayerScreenPos = ImVec2(0, 0);
ImVec2 g_mainPlayerScreenPosBuffered = ImVec2(0, 0);

std::map<HWND, DMARender::RenderWindow*> DMARender::hwndMap = std::map<HWND, DMARender::RenderWindow*>();
void DMARender::RenderWindow::drawOverlayHandler()
{
    static bool identifyWindows = false;
    static bool overlayEnabled = false;
    auto pIO = ImGui::GetPlatformIO();
    static int monitor_current_idx = 0;
    ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);
    ImGui::Begin("Fuser Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);


    static int selectedTab = 0;
    static bool followPlayerEnabled = false;


    // add tabs
    if (ImGui::BeginTabBar("FuserTabs")) {
        // ESP tab
        if (ImGui::BeginTabItem("Fuser")) {
            selectedTab = 0;

            if (identifyWindows) {
                for (int i = 0; i < pIO.Monitors.size(); i++) {
                    auto pMonitor = pIO.Monitors[i];
                    ImGui::SetNextWindowPos(ImVec2(pMonitor.MainPos.x + 40, pMonitor.MainPos.y + 40));
                    ImGui::SetNextWindowSize(ImVec2(150, 250));
                    auto windowName = std::format("{}", i);
                    ImGui::Begin(windowName.c_str(), nullptr, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

                    auto drawList = ImGui::GetWindowDrawList();
                    auto p = ImGui::GetCursorScreenPos();

                    ImGui::PushFont(windowIdentifyFont);
                    drawList->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(p.x, p.y), IM_COL32(255, 0, 0, 255), windowName.c_str());
                    ImGui::PopFont();
                    ImGui::End();
                }
            }

            if (overlayEnabled) {
                auto io = ImGui::GetIO();
                ImGui::Text("FPS: %.1f FPS", io.Framerate);
                if (ImGui::Button("Disable ESP"))
                    overlayEnabled = false;


                bool showPlayerInfoesp = bridge->shouldShowPlayerInfoesp();
                bool showZombiesFUSER = bridge->shouldShowZombiesFUSER();
                bool showAnimalsFUSER = bridge->shouldShowAnimalsFUSER();
                bool showVehiclesFUSER = bridge->shouldShowVehiclesFUSER();
                bool showBoatsFUSER = bridge->shouldShowBoatsFUSER();
                bool showDebugFUSER = bridge->shouldShowDebugFUSER();
                int ZombieDistanceFUSER = bridge->shouldZombieDistanceFUSER();
                int LootDebugDistance = bridge->shouldLootDebugDistance();
                std::string followPlayerName = bridge->shouldPlayerName();


                ImGui::InputText("Name", &followPlayerName, sizeof(followPlayerName));
                ImGui::Checkbox("Name, Dist, Hand", &showPlayerInfoesp);
                ImGui::Checkbox("Zombie Box", &showZombiesFUSER);
                if (showZombiesFUSER) {
                    ImGui::SliderInt("Z Dist", &ZombieDistanceFUSER, 1, 300);
                }
                ImGui::Checkbox("Animals", &showAnimalsFUSER);
                ImGui::Checkbox("Cars", &showVehiclesFUSER);
                ImGui::Checkbox("Boats", &showBoatsFUSER);
                ImGui::Checkbox("Debug Info", &showDebugFUSER);
                if (showDebugFUSER) {
                    ImGui::SliderInt("D Dist", &LootDebugDistance, 1, 300);
                }
                bridge->setShowPlayerInfoesp(showPlayerInfoesp);
                bridge->setShowZombiesFUSER(showZombiesFUSER);
                bridge->setShowAnimalsFUSER(showAnimalsFUSER);
                bridge->setShowVehiclesFUSER(showVehiclesFUSER);
                bridge->setShowBoatsFUSER(showBoatsFUSER);
                bridge->setShowDebugFUSER(showDebugFUSER);
                bridge->setZombieDistance(ZombieDistanceFUSER);
                bridge->setLootDebugDistance(LootDebugDistance);
                bridge->setShowPlayerName(followPlayerName);

            }
            else {
                ImGui::Checkbox("Identify Windows", &identifyWindows);
                std::string comboPreview = std::format("Window {}", monitor_current_idx);

                if (ImGui::BeginCombo("Overlay Monitor", comboPreview.c_str())) {
                    for (int i = 0; i < pIO.Monitors.size(); i++) {
                        auto pMonitor = pIO.Monitors[i];
                        const bool isSelected = (monitor_current_idx == i);
                        auto monitorName = std::format("Monitor {}", i);
                        if (ImGui::Selectable(monitorName.c_str(), isSelected)) {
                            monitor_current_idx = i;
                        }
                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::Text("Selected Resolution: %.0fx%.0f", pIO.Monitors[monitor_current_idx].MainSize.x, pIO.Monitors[monitor_current_idx].MainSize.y);
                if (ImGui::Button("Start ESP")) {
                    overlayEnabled = true;
                    identifyWindows = false;
                }
            }
            //ImGui::End();

            ImGui::EndTabItem();
        }

        // Playerlist Tab
        if (ImGui::BeginTabItem("Loot")) {
            selectedTab = 1;

            bool showDeadPlayersFUSER = bridge->shouldShowDeadPlayersFUSER();
            bool showDeadAnimalsFUSER = bridge->shouldShowDeadAnimalsFUSER();
            bool showBackpacksFUSER = bridge->shouldShowBackpacksFUSER();
            bool showClothingFUSER = bridge->shouldShowClothingFUSER();
            bool showOpticsFUSER = bridge->shouldShowOpticsFUSER();
            bool showExplosivesFUSER = bridge->shouldShowExplosivesFUSER();
            bool showWeaponsFUSER = bridge->shouldShowWeaponsFUSER();
            bool showMeleeFUSER = bridge->shouldShowMeleeFUSER();
            bool showProxyMagazinesFUSER = bridge->shouldShowProxyMagazinesFUSER();
            bool showAmmoFUSER = bridge->shouldShowAmmoFUSER();
            bool showFoodFUSER = bridge->shouldShowFoodFUSER();
            bool showGrounditemsFUSER = bridge->shouldShowGrounditemsFUSER();
            bool showRareFUSER = bridge->shouldShowRareFUSER();
            int showItemDistance = bridge->shouldlootDistanceFUSER();
            bool showBaseFUSER = bridge->shouldShowBaseFUSER();


            ImGui::Text("Loot");
            ImGui::Checkbox("Dead Players", &showDeadPlayersFUSER);
            ImGui::Checkbox("Dead Animals", &showDeadAnimalsFUSER);
            ImGui::Checkbox("Backpacks", &showBackpacksFUSER);
            ImGui::Checkbox("Clothing", &showClothingFUSER);
            ImGui::Checkbox("Optics", &showOpticsFUSER);
            ImGui::Checkbox("Explosives", &showExplosivesFUSER);
            ImGui::Checkbox("Weapons", &showWeaponsFUSER);
            ImGui::Checkbox("Melee", &showMeleeFUSER);
            ImGui::Checkbox("Proxy Magazines", &showProxyMagazinesFUSER);
            ImGui::Checkbox("Ammo", &showAmmoFUSER);
            ImGui::Checkbox("Food", &showFoodFUSER);
            ImGui::Checkbox("Ground Items", &showGrounditemsFUSER);
            ImGui::Checkbox("Base Items", &showBaseFUSER);
            ImGui::Checkbox("Rare (rareitems.txt)", &showRareFUSER);
            ImGui::SliderInt("Distance", &showItemDistance, 1.0, 170);



            bridge->setShowDeadPlayersFUSER(showDeadPlayersFUSER);
            bridge->setShowDeadAnimalsFUSER(showDeadAnimalsFUSER);
            bridge->setShowBackpacksFUSER(showBackpacksFUSER);
            bridge->setShowClothingFUSER(showClothingFUSER);
            bridge->setShowOpticsFUSER(showOpticsFUSER);
            bridge->setShowExplosivesFUSER(showExplosivesFUSER);
            bridge->setShowWeaponsFUSER(showWeaponsFUSER);
            bridge->setShowMeleeFUSER(showMeleeFUSER);
            bridge->setShowProxyMagazinesFUSER(showProxyMagazinesFUSER);
            bridge->setShowAmmoFUSER(showAmmoFUSER);
            bridge->setShowFoodFUSER(showFoodFUSER);
            bridge->setShowGrounditemsFUSER(showGrounditemsFUSER);
            bridge->setShowBaseFUSER(showBaseFUSER);
            bridge->setShowRareFUSER(showRareFUSER);
            bridge->setlootDistance(showItemDistance);




        }
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();

    if (overlayEnabled) {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
        auto selectedMonitor = pIO.Monitors[monitor_current_idx];
        ImGui::SetNextWindowSize(ImVec2(selectedMonitor.MainSize.x, selectedMonitor.MainSize.y));
        ImGui::SetNextWindowPos((ImVec2(selectedMonitor.MainPos.x, selectedMonitor.MainPos.y)));
        ImGui::Begin("ESP", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration);
        this->bridge->getOverlay()->DrawOverlay();
        ImGui::End();
    }
}

void DMARender::RenderWindow::drawMapHandler() {
    // Map Selection and Radar Setup
    auto maps = bridge->getMapManager()->getMaps();
    if (maps.size() == 0)
        return;
    static int map_current_index = 0;
    static MapTransform mTrans = MapTransform();

    ImGui::Begin("Radar Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);

    static int selectedTab = 0;
    static bool followPlayerEnabled = false;


    // add tabs
    if (ImGui::BeginTabBar("RadarTabs")) {
        // ESP tab
        if (ImGui::BeginTabItem("Radar")) {
            selectedTab = 0;

            if (bridge->getMapManager()->isMapSelected()) {
                if (ImGui::Button("Stop Radar"))
                    bridge->getMapManager()->clearMap();
            }
            else {
                auto previewString = maps[map_current_index]->getName();
                if (ImGui::BeginCombo("Map", previewString.c_str())) {
                    for (int i = 0; i < maps.size(); i++) {
                        bool isSelected = i == map_current_index;
                        if (ImGui::Selectable(maps[i]->getName().c_str(), isSelected))
                            map_current_index = i;
                    }
                    ImGui::EndCombo();
                }
                if (ImGui::Button("Start Radar")) {
                    mTrans.mapZoom = 0.3;
                    mTrans.dragOffsetX = 0;
                    mTrans.dragOffsetY = 0;
                    bridge->getMapManager()->selectMap(map_current_index);
                }
            }

            // filter settings and checkbox
            if (bridge->getMapManager()->isMapSelected()) {
                bool showVehicles = bridge->shouldShowVehicles();
                bool showBoats = bridge->shouldShowBoats();
                bool showZombies = bridge->shouldShowZombies();
                bool showAnimals = bridge->shouldShowAnimals();
                int ZombiesBlipSize = bridge->shouldZombiesBlipSize();
                int AnimalsBlipSize = bridge->shouldAnimalsBlipSize();

                std::string followPlayerName = bridge->shouldPlayerName();
                int BlipSize = bridge->shouldBlipSize();
                int Aimlinelength = bridge->shouldAimlinelength();

                // fonts
                int RadarFont = bridge->shouldRadarFont();

                ImGui::Checkbox("Follow Player", &followPlayerEnabled);
                ImGui::InputText("Name", &followPlayerName, sizeof(followPlayerName));
                ImGui::SliderInt("P Blip", &BlipSize, 2, 15);
                ImGui::SliderInt("Aimline", &Aimlinelength, 1, 100);
                ImGui::SliderInt("P Font", &RadarFont, 10, 32);
                ImGui::Checkbox("Zombies", &showZombies);
                if (showZombies) {

                    ImGui::SliderInt("Z Blip", &ZombiesBlipSize, 2, 15);

                }
                ImGui::Checkbox("Animals", &showAnimals);
                if (showAnimals) {

                    ImGui::SliderInt("A Blip", &AnimalsBlipSize, 2, 15);

                }
                ImGui::Checkbox("Cars", &showVehicles);
                ImGui::Checkbox("Boats", &showBoats);
                bridge->setShowVehicles(showVehicles);
                bridge->setShowBoats(showBoats);
                bridge->setShowZombies(showZombies);
                bridge->setShowAnimals(showAnimals);
                bridge->setShowPlayerName(followPlayerName);
                bridge->setShowBlipSize(BlipSize);
                bridge->setAimlinelength(Aimlinelength);
                bridge->setZombiesBlipSize(ZombiesBlipSize);
                bridge->setAnimalsBlipSize(AnimalsBlipSize);

                // font
                bridge->setRadarFont(RadarFont);
            }
            ImGui::EndTabItem();
        }

        // Playerlist Tab
        if (ImGui::BeginTabItem("Loot")) {
            selectedTab = 1;

            bool showDeadPlayers = bridge->shouldShowDeadPlayers();
            bool showGrounditems = bridge->shouldShowGrounditems();
            bool showDeadAnimals = bridge->shouldShowDeadAnimals();
            bool showClothing = bridge->shouldShowClothing();
            bool showExplosives = bridge->shouldShowExplosives();
            bool showWeapons = bridge->shouldShowWeapons();
            bool showMelee = bridge->shouldShowMelee();
            bool showProxyMagazines = bridge->shouldShowProxyMagazines();
            bool showBackpacks = bridge->shouldShowBackpacks();
            bool showFood = bridge->shouldShowFood();
            bool showAmmo = bridge->shouldShowAmmo();
            bool showRare = bridge->shouldShowRare();
            bool showBase = bridge->shouldShowBase();
            bool showOptics = bridge->shouldShowOptics();
            int LootDistanceDeadzone = bridge->shouldLootDistanceDeadzone();
            int BlipSize2 = bridge->shouldBlipSize2();
            int RadarFont2 = bridge->shouldRadarFont2();

            ImGui::Text("Loot");
            ImGui::Checkbox("Dead Players", &showDeadPlayers);
            ImGui::Checkbox("Dead Animals", &showDeadAnimals);
            ImGui::Checkbox("Backpacks", &showBackpacks);
            ImGui::Checkbox("Clothing", &showClothing);
            ImGui::Checkbox("Optics", &showOptics);
            ImGui::Checkbox("Explosives", &showExplosives);
            ImGui::Checkbox("Weapons", &showWeapons);
            ImGui::Checkbox("Melee", &showMelee);
            ImGui::Checkbox("Proxy Magazines", &showProxyMagazines);
            ImGui::Checkbox("Ammo", &showAmmo);
            ImGui::Checkbox("Food", &showFood);
            ImGui::Checkbox("Ground Items", &showGrounditems);
            ImGui::Checkbox("Base Items", &showBase);
            ImGui::Checkbox("Rare (rareitems.txt)", &showRare);
            ImGui::SliderInt("Loot Deadzone", &LootDistanceDeadzone, 0, 300);
            ImGui::SliderInt("Loot Blip", &BlipSize2, 2, 15);
            ImGui::SliderInt("Loot Font", &RadarFont2, 10, 32);

            bridge->setShowDeadPlayers(showDeadPlayers);
            bridge->setShowGrounditems(showGrounditems);
            bridge->setShowDeadAnimals(showDeadAnimals);
            bridge->setShowClothing(showClothing);
            bridge->setShowExplosives(showExplosives);
            bridge->setShowWeapons(showWeapons);
            bridge->setShowMelee(showMelee);
            bridge->setShowProxyMagazines(showProxyMagazines);
            bridge->setShowBackpacks(showBackpacks);
            bridge->setShowFood(showFood);
            bridge->setShowAmmo(showAmmo);
            bridge->setShowRare(showRare);
            bridge->setShowBase(showBase);
            bridge->setShowOptics(showOptics);
            bridge->setLootDistanceDeadzone(LootDistanceDeadzone);
            bridge->setShowBlipSize2(BlipSize2);
            bridge->setRadarFont2(RadarFont2);


            // filter settings and checkbox
            //bool showPlayerList = bridge->shouldShowPlayerList();
            //bool showServerPlayerList = bridge->shouldShowServerPlayerList();

            //ImGui::Checkbox("Enable Player List", &showPlayerList);
            //ImGui::Checkbox("Enable Server Player List", &showServerPlayerList);

            //ImGui::InputText("Player Name", &followPlayerName, sizeof(&followPlayerName));

            //bridge->setName(followPlayerName);

            //bridge->setShowPlayerList(showPlayerList);
            //bridge->setShowServerPlayerList(showServerPlayerList);

            ImGui::EndTabItem();
        }
        // Playerlist Tab
        if (ImGui::BeginTabItem("Extra")) {
            selectedTab = 2;

            bool showPlayerList = bridge->shouldShowPlayerList();
            bool showServerPlayerList = bridge->shouldShowServerPlayerList();

            ImGui::Checkbox("Player List", &showPlayerList);
            ImGui::Checkbox("Server Player List", &showServerPlayerList);

            bridge->setShowPlayerList(showPlayerList);
            bridge->setShowServerPlayerList(showServerPlayerList);


            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End(); // close mainwindow

    //Radar Logic
    if (!bridge->getMapManager()->isMapSelected())
        return;
    auto gameMap = bridge->getMapManager()->getSelectedGameMap();
    auto allocator = bridge->getMapManager()->getSelectedAllocator();
    if (!gameMap || !allocator)
        return;

    RECT rect;
    GetWindowRect(hwnd, &rect);


    if (mTrans.mapZoom < 0) {
        float mapSize = fmaxf(allocator->getWidth(), allocator->getHeight());
        float screenSize = fminf(rect.right - rect.left, rect.bottom - rect.top);
        mTrans.mapZoom = screenSize / mapSize;
        mTrans.mapHeight = allocator->getHeight();
        mTrans.mapWidth = allocator->getWidth();
    }

    auto mousePos = ImGui::GetMousePos();
    static float lastMousePosX = mousePos.x;
    static float lastMousePosY = mousePos.y;

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && !ImGui::GetIO().WantCaptureMouse) {
        mTrans.dragOffsetX += mousePos.x - lastMousePosX;
        mTrans.dragOffsetY += mousePos.y - lastMousePosY;
    }
    if (ImGui::GetIO().MouseWheel != 0.0f) {
        float oldZoom = mTrans.mapZoom;
        //Zoom in/out
        mTrans.mapZoom *= (1 + (ImGui::GetIO().MouseWheel * .05));
        if (mTrans.mapZoom < 0.01)
            mTrans.mapZoom = 0.01;

        //Zoom toward cursor
        float deltaX = (allocator->getWidth() * oldZoom) - (allocator->getWidth() * mTrans.mapZoom);
        float deltaY = (allocator->getHeight() * oldZoom) - (allocator->getHeight() * mTrans.mapZoom);

        float percX = (mousePos.x - rect.left - mTrans.dragOffsetX) / ((allocator->getWidth() * mTrans.mapZoom));
        float percY = (mousePos.y - rect.top - mTrans.dragOffsetY) / ((allocator->getHeight() * mTrans.mapZoom));

        mTrans.dragOffsetX += (deltaX * percX);
        mTrans.dragOffsetY += (deltaY * percY);
    }

    lastMousePosX = mousePos.x;
    lastMousePosY = mousePos.y;

    // **Update gepufferte Spielerposition vor Nutzung**
    g_mainPlayerScreenPosBuffered = g_mainPlayerScreenPos;

    // Falls Follow Player aktiviert ist, passe mTrans basierend auf der Fenstergröße an
    if (followPlayerEnabled) {
        float winWidth = static_cast<float>(rect.right - rect.left);
        float winHeight = static_cast<float>(rect.bottom - rect.top);
        float centerX = winWidth / 2.0f;
        float centerY = winHeight / 2.0f;

      
        float desiredOffsetX = centerX - g_mainPlayerScreenPosBuffered.x;
        float desiredOffsetY = centerY - g_mainPlayerScreenPosBuffered.y;

        // Debugging
        //std::cout << "Fensterzentrum: (" << centerX << ", " << centerY << ")\n";
        //std::cout << "MainPlayerPos (Buffered): (" << g_mainPlayerScreenPosBuffered.x << ", " << g_mainPlayerScreenPosBuffered.y << ")\n";
        //std::cout << "Gewünschter Offset: (" << desiredOffsetX << ", " << desiredOffsetY << ")\n";
        //std::cout << "Aktueller Offset: (" << mTrans.dragOffsetX << ", " << mTrans.dragOffsetY << ")\n";

        // Schwellwert: nur anpassen, wenn der Unterschied größer als z. B. 5 Pixel ist
        const float threshold = 5.0f;
        if (fabs(desiredOffsetX - mTrans.dragOffsetX) > threshold) {
            mTrans.dragOffsetX = desiredOffsetX;
        }
        if (fabs(desiredOffsetY - mTrans.dragOffsetY) > threshold) {
            mTrans.dragOffsetY = desiredOffsetY;
        }
    }


    ImDrawList* fgDrawList = ImGui::GetBackgroundDrawList();
    fgDrawList->AddImage(
        allocator->getImage(),
        ImVec2(
            rect.left + mTrans.dragOffsetX,
            rect.top + mTrans.dragOffsetY
        ),
        ImVec2(
            rect.left + mTrans.dragOffsetX + (allocator->getWidth() * mTrans.mapZoom),
            rect.top + mTrans.dragOffsetY + (allocator->getHeight() * mTrans.mapZoom)
        )
    );
    this->bridge->getRadar()->DrawOverlay(bridge->getMapManager()->getSelectedGameMap().get(), mTrans);
    
}

DMARender::RenderWindow::RenderWindow()
{
    g_pd3dDevicePtr = new ID3D11Device*;
    this->bridge = std::shared_ptr<RenderBridge>(new RenderBridge(g_pd3dDevicePtr));
}

void DMARender::RenderWindow::_setResizeParams(UINT width, UINT height)
{
    this->g_ResizeWidth = width;
    this->g_ResizeHeight = height;
}

void DMARender::RenderWindow::initializeWindow()
{
    // Create application window
    ImGui_ImplWin32_EnableDpiAwareness();

    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, DMARender::WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    hwnd = ::CreateWindowW(wc.lpszClassName, L"DayZ-DMA-Radar",  WS_OVERLAPPEDWINDOW, 0, 0, 1600, 900, nullptr, nullptr, wc.hInstance, nullptr);
    DMARender::hwndMap[hwnd] = this;

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_MAXIMIZE);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    CreateFonts();
    this->bridge->createFonts();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
    *g_pd3dDevicePtr = g_pd3dDevice;




    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (this->bridge != nullptr) {
            drawMapHandler();
            if (this->bridge->getOverlay() != nullptr) {
                drawOverlayHandler();
            }
        }

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        //g_pSwapChain->Present(1, 0); // Present with vsync
        g_pSwapChain->Present(0, 0); // Present without vsync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return;
}

std::shared_ptr<DMARender::RenderBridge> DMARender::RenderWindow::getBridge()
{
    return this->bridge;
}

// Helper functions
bool DMARender::RenderWindow::CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void DMARender::RenderWindow::CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void DMARender::RenderWindow::CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    if (pBackBuffer != NULL) {
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
        pBackBuffer->Release();
    }

}

void DMARender::RenderWindow::CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

void DMARender::RenderWindow::CreateFonts()
{
    ImGui::GetIO().Fonts->AddFontDefault();
    ImFontConfig config;
    config.OversampleH = 2;
    config.OversampleV = 1;
    config.GlyphExtraSpacing.x = 1.0f;
    windowIdentifyFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 256, &config);
}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT WINAPI DMARender::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
    {
        if (wParam == SIZE_MINIMIZED)
            return 0;
        RenderWindow* rndPtr = DMARender::hwndMap[hWnd];
        rndPtr->_setResizeParams((UINT)LOWORD(lParam), (UINT)HIWORD(lParam)); // Queue resize
        return 0;
    }
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

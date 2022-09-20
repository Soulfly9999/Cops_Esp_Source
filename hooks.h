
void *getTransform(void *player) {
    if (!player) return NULL;
    static const auto get_transform_injected = reinterpret_cast<uint64_t(__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so", 0x117C23C)); //Component::get_transform
    return (void *) get_transform_injected(player);
}
Vector3 get_position(void *transform) {
    if (!transform)return Vector3();
    Vector3 position;
    static const auto get_position_injected = reinterpret_cast<uint64_t(__fastcall *)(void *,Vector3 &)>(getAbsoluteAddress("libil2cpp.so", 0x14C8298)); // Transform::get_position_Injected
    get_position_injected(transform, position);
    return position;
}
Vector3 WorldToScreenPoint(void *transform, Vector3 test) {
    if (!transform)return Vector3();
    Vector3 position;
    static const auto WorldToScreenPoint_Injected = reinterpret_cast<uint64_t(__fastcall *)(void *,Vector3, int, Vector3 &)>(getAbsoluteAddress("libil2cpp.so", 0x1173770)); //Camera::WorldToViewportPoint_Injected
      WorldToScreenPoint_Injected(transform, test, 4, position);
      return position;
}
void *get_camera() {
    static const auto get_camera_injected = reinterpret_cast<uint64_t(__fastcall *)()>(getAbsoluteAddress("libil2cpp.so", 0x1174644)); //Camera::get_main()
    return (void *) get_camera_injected();
}
Vector3 GetPlayerLocation(void *player) {
    return get_position(getTransform(player));
}
int GetPlayerHealth(void *player) {
    if (!player) return NULL;
    static const auto get_Health = reinterpret_cast<uint64_t(__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so", 0x767974)); //Character::get_health()
    return (int) get_Health(player);
}

bool PlayerAlive(void *player) {
    return player != NULL && GetPlayerHealth(player) > 0;
}

bool IsPlayerDead(void *player) {
    return player == NULL && GetPlayerHealth(player) < 1;
}

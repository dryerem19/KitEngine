#pragma once
#include <ode/ode.h>

extern dWorldID g_worldId;
extern dSpaceID g_spaceId;
extern dJointGroupID g_contactGroup;

class PhysicObject
{
private:
    dBodyID mBody;
public:
    PhysicObject()
    {
        // Создание физического тела
        mBody = dBodyCreate(g_worldId);

        // Поместим объект в нулевые координаты по умолчанию
        dBodySetPosition(mBody, 0, 0, 0);
    }

    void SetPosition(const dReal& x, const dReal& y, const dReal& z)
    {
        dBodySetPosition(mBody, x, y, z);
    }
};

static void Simulate()
{
    // Определяет, какие пары геометрических фигур потенциально могут пересекаться
    // Функция обратного вызова отвечает за то, какие из потенциальных пересечений являются столкновениями
    // Второй параметр - указатель на любые данные, которые мы хотим передать в функцию
    dSpaceCollide(g_spaceId, 0, &nearCallback);

    // Быстрая, но менее точная симуляция
    dWorldQuickStep(g_worldId, 0.05);

    // Удалить временные соединения после симуляции
    dJointGroupEmpty(g_contactGroup);
}

static void nearCallback(void* data, dGeomID gId1, dGeomID gId2)
{
    // Временные индекс для контакта
    int index;

    dBodyID b1 = dGeomGetBody(gId1);
    dBodyID b2 = dGeomGetBody(gId2);
}

static void InitPhysics()
{
    // Создание пустого физического мира
    g_worldId = dWorldCreate();

    // Создание пространства столкновений, подходит для небольшого кол-ва объектов
    g_spaceId = dSimpleSpaceCreate(0);

    // Создание коллекции соединений
    g_contactGroup = dJointGroupCreate(0);

    // Плоскость земли
    dCreatePlane(g_spaceId, 0, 1, 0, 0);

    // Установка гравитации Земли
    dWorldSetGravity(g_worldId, 0, -9.81, 0);

    // Контролируют частоту исправления ошибок в просчёте физики
    dWorldSetERP(World, 0.2);
    dWorldSetCFM(World, 1e-5);    

    // Скорость разделения взаимопроникающих объектов
    dWorldSetContactMaxCorrectingVel(World, 0.9);    

    // Глубина поверхностного слоя между объектами
    dWorldSetContactSurfaceLayer(World, 0.001);

    // Остановить моделирование физики для объектов, которые остановились
    dWorldSetAutoDisableFlag(World, 1);
}

static void DeletePhysics()
{
    // Удалить все соединения из группы
    dJointGroupDestroy(g_contactGroup);

    // Удалить пространство коллизии
    dSpaceDestroy(g_spaceId);

    // Удалить физический мир
    dWorldDestroy(g_worldId);
}
#include "pch.h" 
/****************************************************************************
** Meta object code from reading C++ file 'SEWindowScenntShot.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SEQtMoc/SEWindowScenntShot.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SEWindowScenntShot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN18SEWindowScenntShotE_t {};
} // unnamed namespace

template <> constexpr inline auto SEWindowScenntShot::qt_create_metaobjectdata<qt_meta_tag_ZN18SEWindowScenntShotE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SEWindowScenntShot",
        "__startScreenshot",
        "",
        "onScreenshotSelected",
        "rect"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal '__startScreenshot'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onScreenshotSelected'
        QtMocHelpers::SlotData<void(const QRect &)>(3, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QRect, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SEWindowScenntShot, qt_meta_tag_ZN18SEWindowScenntShotE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SEWindowScenntShot::staticMetaObject = { {
    QMetaObject::SuperData::link<SEScenntShotInter::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18SEWindowScenntShotE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18SEWindowScenntShotE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18SEWindowScenntShotE_t>.metaTypes,
    nullptr
} };

void SEWindowScenntShot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SEWindowScenntShot *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->__startScreenshot(); break;
        case 1: _t->onScreenshotSelected((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SEWindowScenntShot::*)()>(_a, &SEWindowScenntShot::__startScreenshot, 0))
            return;
    }
}

const QMetaObject *SEWindowScenntShot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SEWindowScenntShot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18SEWindowScenntShotE_t>.strings))
        return static_cast<void*>(this);
    return SEScenntShotInter::qt_metacast(_clname);
}

int SEWindowScenntShot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SEScenntShotInter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SEWindowScenntShot::__startScreenshot()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP

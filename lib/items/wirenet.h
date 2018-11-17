#pragma once

#include <QObject>
#include <QList>
#include <QSharedPointer>
#include <memory>
#include "line.h"
#include "wirenetlabel.h"

namespace QSchematic {

    class Wire;
    class WirePoint;

    class WireNet : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(WireNet)

    public:
        WireNet(QObject* parent = nullptr);
        virtual ~WireNet() override;

        bool addWire(Wire& wire);
        bool removeWire(Wire& wire);
        bool contains(const Wire& wire) const;
        int removeDuplicatePoints();
        int removeObsoletePoints();
        void setName(const QString& name);
        void setHighlighted(bool highlighted);

        QString name() const;
        QList<Wire*> wires() const;
        QList<Line> lineSegments() const;
        QList<QPoint> points() const;
        WireNetLabel& label();  // Only use this to add the label to the scene!!!

        void updateWireJunctions();

    signals:
        void pointMoved(Wire& wire, WirePoint& point);
        void highlightChanged(bool highlighted);

    private slots:
        void wirePointMoved(Wire& wire, WirePoint& point);
        void labelHighlightChanged(const Item& item, bool highlighted);
        void wireHighlightChanged(const Item& item, bool highlighted);

    private:
        QList<Wire*> _wires;
        QString _name;
        WireNetLabel _label;
    };

}
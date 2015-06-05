#include "gpropitemfactory.h"
#include "gpropitem_base.h"
#include "gpropitem_bool.h"
#include "gpropitem_qchar.h"
#include "gpropitem_unknowntype.h"

// ----------------------------------------------------------------------------
// GPropItemFactoryInstance
// ----------------------------------------------------------------------------
class GPropItemFactoryInstance : public GPropItemFactory
{
public:
  GPropItemFactoryInstance()
  {
    append(new GPropItemCreator_Bool);
    append(new GPropItemCreator_Base(QMetaType::Int));
    append(new GPropItemCreator_Base(QMetaType::UInt));
    append(new GPropItemCreator_Base(QMetaType::LongLong));
    append(new GPropItemCreator_Base(QMetaType::ULongLong));
    append(new GPropItemCreator_Base(QMetaType::Double));
    append(new GPropItemCreator_QChar);

    append(new GPropItemCreator_Base(QMetaType::QString));

  }

  /*
        * Invalid = QMetaType::UnknownType,
        * Bool = QMetaType::Bool,
        * Int = QMetaType::Int,
        * UInt = QMetaType::UInt,
        * LongLong = QMetaType::LongLong,
        * ULongLong = QMetaType::ULongLong,
        * Double = QMetaType::Double,
        * Char = QMetaType::QChar,
        Map = QMetaType::QVariantMap,
        List = QMetaType::QVariantList,
        String = QMetaType::QString,
        StringList = QMetaType::QStringList,
        ByteArray = QMetaType::QByteArray,
        BitArray = QMetaType::QBitArray,
        Date = QMetaType::QDate,
        Time = QMetaType::QTime,
        DateTime = QMetaType::QDateTime,
        Url = QMetaType::QUrl,
        Locale = QMetaType::QLocale,
        Rect = QMetaType::QRect,
        RectF = QMetaType::QRectF,
        Size = QMetaType::QSize,
        SizeF = QMetaType::QSizeF,
        Line = QMetaType::QLine,
        LineF = QMetaType::QLineF,
        Point = QMetaType::QPoint,
        PointF = QMetaType::QPointF,
        RegExp = QMetaType::QRegExp,
        RegularExpression = QMetaType::QRegularExpression,
        Hash = QMetaType::QVariantHash,
        EasingCurve = QMetaType::QEasingCurve,
        Uuid = QMetaType::QUuid,
        ModelIndex = QMetaType::QModelIndex,
        LastCoreType = QMetaType::LastCoreType,

        Font = QMetaType::QFont,
        Pixmap = QMetaType::QPixmap,
        Brush = QMetaType::QBrush,
        Color = QMetaType::QColor,
        Palette = QMetaType::QPalette,
        Image = QMetaType::QImage,
        Polygon = QMetaType::QPolygon,
        Region = QMetaType::QRegion,
        Bitmap = QMetaType::QBitmap,
        Cursor = QMetaType::QCursor,
        KeySequence = QMetaType::QKeySequence,
        Pen = QMetaType::QPen,
        TextLength = QMetaType::QTextLength,
        TextFormat = QMetaType::QTextFormat,
        Matrix = QMetaType::QMatrix,
        Transform = QMetaType::QTransform,
        Matrix4x4 = QMetaType::QMatrix4x4,
        Vector2D = QMetaType::QVector2D,
        Vector3D = QMetaType::QVector3D,
        Vector4D = QMetaType::QVector4D,
        Quaternion = QMetaType::QQuaternion,
        PolygonF = QMetaType::QPolygonF,
        Icon = QMetaType::QIcon,
        LastGuiType = QMetaType::LastGuiType,

        SizePolicy = QMetaType::QSizePolicy,

        UserType = QMetaType::User
   */
  virtual ~GPropItemFactoryInstance()
  {
    // memory leak // gilgil temp 2105.03.18
  }
};

// ----------------------------------------------------------------------------
// GPropItemFactory
// ----------------------------------------------------------------------------
GPropItem* GPropItemFactory::createItem(GPropItemParam param)
{
  GPropItem* item = nullptr;
  for (QList<GPropItemCreator*>::iterator it = begin(); it != end(); it++)
  {
    GPropItemCreator* creator = *it;
    item = creator->createItem(param);
    if (item != nullptr) break;
  }
  return item;
}

GPropItemFactory& GPropItemFactory::instance()
{
  static GPropItemFactoryInstance factory;
  return factory;
}

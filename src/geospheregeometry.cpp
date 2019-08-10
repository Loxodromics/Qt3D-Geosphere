//
//  geospheregeometry.cpp
//  Qt3D-Geosphere
//
//  Created by philipp on 08.08.2019.
//  Copyright (c) 2019 Philipp Engelhard. All rights reserved.
//
#include "geospheregeometry.h"
#include <QVector3D>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBufferDataGenerator>
#include <Qt3DRender/qbuffer.h>

#include <QDebug>

#include <limits>
#include <stdlib.h>

using namespace Qt3DRender;

namespace {

QByteArray createGeosphereMeshVertexData(int subdevisions, float radius)
{
	Q_UNUSED(subdevisions);
	Q_UNUSED(radius);
	const float X = 0.525731112119133606f;
	const float Z = 0.850650808352039932f;

	/// Vertices
	const auto vertices = QVector<QVector3D>()
	  << QVector3D(-X, 0.0f, Z) << QVector3D(X, 0.0f, Z) << QVector3D(-X, 0.0f, -Z)

	  << QVector3D(X, 0.0f, -Z) << QVector3D(0.0f, Z, X) << QVector3D(0.0f, Z, -X)

	  << QVector3D(0.0f, -Z, X) << QVector3D(0.0f, -Z, -X) << QVector3D(Z, X, 0.0f)

	  << QVector3D(-Z, X, 0.0f) << QVector3D(Z, -X, 0.0f) << QVector3D(-Z, -X, 0.0f);

	QByteArray bufferBytes;
	/// vec3 pos and vec3 normal
	const quint32 elementSize = 3 + 3;
	const quint32 stride = elementSize * sizeof(float);
	const int nVerts = 20;
	bufferBytes.resize(stride * nVerts);

	float* fptr = reinterpret_cast<float*>(bufferBytes.data());

	for (auto vertex : vertices) {
		*fptr++ = vertex.x();
		*fptr++ = vertex.y();
		*fptr++ = vertex.z();

		auto normal = vertex.normalized();
		*fptr++ = normal.x();
		*fptr++ = normal.y();
		*fptr++ = normal.z();
	}
	return bufferBytes;
}

QByteArray createGeosphereMeshIndexData(int subdevisions)
{
	Q_UNUSED(subdevisions);
	int faces = 20;

	QByteArray indexBytes;
	const int indices = faces * 3;
	Q_ASSERT(indices < 65536);
	indexBytes.resize(indices * sizeof(quint16));
	quint16* indexPtr = reinterpret_cast<quint16*>(indexBytes.data());

	// clang-format off
	const std::vector<quint16> rawIndices = { 1, 4, 0,
										   4, 9, 0,
										   4, 5, 9,
										   8, 5, 4,
										   1, 8, 4,
										   1, 10, 8,
										   10, 3, 8,
										   8, 3, 5,
										   3, 2, 5,
										   3, 7, 2,
										   3, 10, 7,
										   10, 6, 7,
										   6, 11, 7,
										   6, 0, 11,
										   6, 1, 0,
										   10, 1, 6,
										   11, 0, 9,
										   2, 11, 9,
										   5, 2, 9,
										   11, 2, 7 };
	// clang-format on

	for (const auto each : rawIndices) {
		*indexPtr++ = each;
	}

	return indexBytes;
}

}	// anonymous

class GeosphereVertexDataFunctor : public Qt3DRender::QBufferDataGenerator {
public:
	GeosphereVertexDataFunctor(int subdevisions, float radius)
		: m_subdevisions(subdevisions)
		, m_radius(radius)
	{
	}

	QByteArray operator()() override { return createGeosphereMeshVertexData(m_subdevisions, m_radius); }

	bool operator==(const QBufferDataGenerator& other) const override
	{
		const GeosphereVertexDataFunctor* otherFunctor = functor_cast<GeosphereVertexDataFunctor>(&other);
		if (otherFunctor != nullptr)
			return (otherFunctor->m_subdevisions == m_subdevisions
			  && otherFunctor->m_radius == m_radius);
		return false;
	}

	QT3D_FUNCTOR(GeosphereVertexDataFunctor)

private:
	int m_subdevisions;
	float m_radius;
};

class GeosphereIndexDataFunctor : public QBufferDataGenerator {
public:
	GeosphereIndexDataFunctor(int subdevisions)
		: m_subdevisions(subdevisions)
	{
	}

	QByteArray operator()() override { return createGeosphereMeshIndexData(m_subdevisions); }

	bool operator==(const QBufferDataGenerator& other) const override
	{
		const GeosphereIndexDataFunctor* otherFunctor = functor_cast<GeosphereIndexDataFunctor>(&other);
		if (otherFunctor != nullptr)
			return (otherFunctor->m_subdevisions == m_subdevisions);
		return false;
	}

	QT3D_FUNCTOR(GeosphereIndexDataFunctor)

private:
	int m_subdevisions;
};

GeosphereGeometry::GeosphereGeometry(Qt3DCore::QNode* parent)
	: Qt3DRender::QGeometry(parent)
	, m_positionAttribute(nullptr)
	, m_indexAttribute(nullptr)
	, m_normalAttribute(nullptr)
	, m_vertexBuffer(nullptr)
	, m_indexBuffer(nullptr)
{
	this->init();
}

GeosphereGeometry::~GeosphereGeometry() {}

QAttribute* GeosphereGeometry::positionAttribute() const { return this->m_positionAttribute; }

QAttribute* GeosphereGeometry::indexAttribute() const { return this->m_indexAttribute; }

QAttribute* GeosphereGeometry::normalAttribute() const { return this->m_normalAttribute; }

void GeosphereGeometry::init()
{
	m_positionAttribute = new QAttribute(this);
	m_indexAttribute = new QAttribute(this);
	m_normalAttribute = new QAttribute(this);
	m_vertexBuffer = new Qt3DRender::QBuffer(this);
	m_indexBuffer = new Qt3DRender::QBuffer(this);

	const int nVerts = 20 * 3;
	/// vec3 pos, vec3 normal
	const int stride = (3 + 3) * sizeof(float);
	const int faces = 20;

	m_positionAttribute->setName(QAttribute::defaultPositionAttributeName());
	m_positionAttribute->setVertexBaseType(QAttribute::Float);
	m_positionAttribute->setVertexSize(3);
	m_positionAttribute->setAttributeType(QAttribute::VertexAttribute);
	m_positionAttribute->setBuffer(m_vertexBuffer);
	m_positionAttribute->setByteStride(stride);
	m_positionAttribute->setCount(nVerts);

	m_normalAttribute->setName(QAttribute::defaultNormalAttributeName());
	m_normalAttribute->setVertexBaseType(QAttribute::Float);
	m_normalAttribute->setVertexSize(3);
	m_normalAttribute->setAttributeType(QAttribute::VertexAttribute);
	m_normalAttribute->setBuffer(m_vertexBuffer);
	m_normalAttribute->setByteStride(stride);
	m_normalAttribute->setByteOffset(3 * sizeof(float));
	m_normalAttribute->setCount(nVerts);

	m_indexAttribute->setAttributeType(QAttribute::IndexAttribute);
	m_indexAttribute->setVertexBaseType(QAttribute::UnsignedShort);
	m_indexAttribute->setBuffer(m_indexBuffer);

	/// Each primitive has 3 vertives
	m_indexAttribute->setCount(faces * 3);

	m_vertexBuffer->setDataGenerator(QSharedPointer<GeosphereVertexDataFunctor>::create(1, 1.0f));
	m_indexBuffer->setDataGenerator(QSharedPointer<GeosphereIndexDataFunctor>::create(1));

	this->addAttribute(m_positionAttribute);
	this->addAttribute(m_normalAttribute);
	this->addAttribute(m_indexAttribute);
}


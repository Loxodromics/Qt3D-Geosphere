//
//  geospheregeometry.cpp
//  Qt3D-Geosphere
//
//  Created by philipp on 08.08.2019.
//  Copyright (c) 2019 Philipp Engelhard. All rights reserved.
//
#include "geospheregeometry.h"
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/qbuffer.h>
#include <QVector3D>

#include <QDebug>

#include <limits>
#include <stdlib.h>

using namespace Qt3DRender;


GeosphereGeometry::GeosphereGeometry(Qt3DCore::QNode *parent)
	: Qt3DRender::QGeometry(parent)
	, m_positionAttribute(nullptr)
	, m_normalAttribute(nullptr)
	, m_vertexBuffer(nullptr)
{
	this->init();
}

GeosphereGeometry::~GeosphereGeometry(){}

QAttribute* GeosphereGeometry::positionAttribute() const
{
	return this->m_positionAttribute;
}

QAttribute* GeosphereGeometry::normalAttribute() const
{
	return this->m_normalAttribute;
}

void GeosphereGeometry::init()
{
	m_positionAttribute = new QAttribute(this);
	m_normalAttribute = new QAttribute(this);
	m_vertexBuffer = new Qt3DRender::QBuffer(this);

	const int nVerts = 20 * 3;
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

	this->addAttribute(m_positionAttribute);
	this->addAttribute(m_normalAttribute);

	this->fillBuffers();
}

void GeosphereGeometry::fillBuffers()
{
	const float X = 0.525731112119133606f;
	const float Z = 0.850650808352039932f;

	// Vertices
	const auto v0 = QVector3D(-X, 0.0f, Z);
	const auto v1 = QVector3D(X, 0.0f, Z);
	const auto v2 = QVector3D(-X, 0.0f, -Z);

	const auto v3 = QVector3D(X, 0.0f, -Z);
	const auto v4 = QVector3D(0.0f, Z, X);
	const auto v5 = QVector3D(0.0f, Z, -X);

	const auto v6 = QVector3D(0.0f, -Z, X);
	const auto v7 = QVector3D(0.0f, -Z, -X);
	const auto v8 = QVector3D(Z, X, 0.0f);

	const auto v9 = QVector3D(-Z, X, 0.0f);
	const auto v10 = QVector3D(Z, -X, 0.0f);
	const auto v11 = QVector3D(-Z, -X, 0.0f);

	const auto n1v4v0 = QVector3D::normal(v1, v4, v0);
	const auto n4v9v0 = QVector3D::normal(v4, v9, v0);
	const auto n4v5v9 = QVector3D::normal(v4, v5, v9);
	const auto n8v5v4 = QVector3D::normal(v8, v5, v4);
	const auto n1v8v4 = QVector3D::normal(v1, v8, v4);
	const auto n1v10v8 = QVector3D::normal(v1, v10, v8);
	const auto n10v3v8 = QVector3D::normal(v10, v3, v8);
	const auto n8v3v5 = QVector3D::normal(v8, v3, v5);
	const auto n3v2v5 = QVector3D::normal(v3, v2, v5);
	const auto n3v7v2 = QVector3D::normal(v3, v7, v2);
	const auto n3v10v7 = QVector3D::normal(v3, v10, v7);
	const auto n10v6v7 = QVector3D::normal(v10, v6, v7);
	const auto n6v11v7 = QVector3D::normal(v6, v11, v7);
	const auto n6v0v11 = QVector3D::normal(v6, v0, v11);
	const auto n6v1v0 = QVector3D::normal(v6, v1, v0);
	const auto n10v1v6 = QVector3D::normal(v10, v1, v6);
	const auto n11v0v9 = QVector3D::normal(v11, v0, v9);
	const auto n2v11v9 = QVector3D::normal(v2, v11, v9);
	const auto n5v2v9 = QVector3D::normal(v5, v2, v9);
	const auto n11v2v7 = QVector3D::normal(v11, v2, v7);

	/// interleaved buffer
	const auto vertices = QVector<QVector3D>()
							<< v1 << n1v4v0 << v4 << n1v4v0 << v0 << n1v4v0
							<< v4 << n4v9v0 << v9 << n4v9v0 << v0 << n4v9v0
							<< v4 << n4v5v9 << v5 << n4v5v9 << v9 << n4v5v9
							<< v8 << n8v5v4 << v5 << n8v5v4 << v4 << n8v5v4
							<< v1 << n1v8v4 << v8 << n1v8v4 << v4 << n1v8v4
							<< v1 << n1v10v8 << v10 << n1v10v8 << v8 << n1v10v8
							<< v10 << n10v3v8 << v3 << n10v3v8 << v8 << n10v3v8
							<< v8 << n8v3v5 << v3 << n8v3v5 << v5 << n8v3v5
							<< v3 << n3v2v5 << v2 << n3v2v5 << v5 << n3v2v5
							<< v3 << n3v7v2 << v7 << n3v7v2 << v2 << n3v7v2
							<< v3 << n3v10v7 << v10 << n3v10v7 << v7 << n3v10v7
							<< v10 << n10v6v7 << v6 << n10v6v7 << v7 << n10v6v7
							<< v6 << n6v11v7 << v11 << n6v11v7 << v7 << n6v11v7
							<< v6 << n6v0v11 << v0 << n6v0v11 << v11 << n6v0v11
							<< v6 << n6v1v0 << v1 << n6v1v0 << v0 << n6v1v0
							<< v10 << n10v1v6 << v1 << n10v1v6 << v6 << n10v1v6
							<< v11 << n11v0v9 << v0 << n11v0v9 << v9 << n11v0v9
							<< v2 << n2v11v9 << v11 << n2v11v9 << v9 << n2v11v9
							<< v5 << n5v2v9 << v2 << n5v2v9 << v9 << n5v2v9
							<< v11 << n11v2v7 << v2 << n11v2v7 << v7 << n11v2v7;

	auto positionsBufferData = QByteArray();
	positionsBufferData.resize(vertices.size() * sizeof(QVector3D));
	auto rawPositionData = reinterpret_cast<QVector3D *>(positionsBufferData.data());
	memcpy(rawPositionData, vertices.constData(), vertices.size() * sizeof(QVector3D));

	m_vertexBuffer->setData(positionsBufferData);
}

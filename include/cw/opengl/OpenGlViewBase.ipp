

namespace cw
{
  namespace opengl
  {

template<typename Coord>
void addNormal( std::vector<GLfloat> & vertexNormals, Coord normal )
{
  vertexNormals.push_back( normal.x );
  vertexNormals.push_back( normal.y );
  vertexNormals.push_back( normal.z );
}

inline void storeDataInGPU( GLuint bufferId, const std::vector< GLfloat > & what )
{
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBufferData(GL_ARRAY_BUFFER,
      what.size() * sizeof(what[0]),
      &what[0],
      GL_STATIC_DRAW );
}

template<typename Iterator>
glm::vec3 createVec3(Iterator iter)
{
  glm::vec3 ret;
  ret.x = *(iter);
  ret.y = *(iter + 1);
  ret.z = *(iter + 2);
  return ret;
}

/// Methods

template<typename ModelType>
OpenGlViewBase<ModelType>::OpenGlViewBase( typename Ref<ModelType>::R model, ProjectionView & projView )
  : m_model( model )
  , m_programId( projView.getProgramId() )
  , m_projView( projView )
  , m_shaderResourceLocator( projView.getProgramId() )
  , m_attribLocation_position(m_shaderResourceLocator.getAttrib("inPosition"))
  , m_attribLocation_normal(m_shaderResourceLocator.getAttrib("inNormal"))
{
  m_colorUniformId = m_shaderResourceLocator.getUniform( "currentColor" );
  glGenVertexArrays(1, &m_vaoId);
  glBindVertexArray( m_vaoId );
  initializeVBOs();
}

template<typename ModelType>
void OpenGlViewBase<ModelType>::initializeVBOs()
{
  glGenBuffers(1, &m_vertexBufferId);
  glGenBuffers(1, &m_normalBufferId);
}

template<typename ModelType>
void OpenGlViewBase<ModelType>::show()
{
  setUpDraw();
  
  glEnableVertexAttribArray( m_attribLocation_position );
  glEnableVertexAttribArray( m_attribLocation_normal );

  doShow();

  glDisableVertexAttribArray( m_attribLocation_position );
  glDisableVertexAttribArray( m_attribLocation_normal );
}

template<typename ModelType>
void OpenGlViewBase<ModelType>::setUpDraw()
{
  glBindVertexArray( m_vaoId );
}

template<typename ModelType>
void OpenGlViewBase<ModelType>::sendMVP( const glm::mat4 & model )
{
  glm::mat4 normalMatrix = glm::transpose( glm::inverse( model ) );
  // TODO use ShaderResourceLocator
  auto normalMatrixId = m_shaderResourceLocator.getUniform( "normalMatrix" );
  glUniformMatrix4fv(normalMatrixId, 1, GL_FALSE, &normalMatrix[0][0]);
  m_projView.sendMVP( model );
}

template<typename ModelType>
void OpenGlViewBase<ModelType>::setModelVertices( const std::vector<GLfloat> & vertices )
{
  m_vertexBuffer.assign( vertices.begin(), vertices.end() );
  storeDataInGPU( m_vertexBufferId, m_vertexBuffer );
  glEnableVertexAttribArray( m_attribLocation_position );
  glVertexAttribPointer( m_attribLocation_position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

template<typename ModelType>
void OpenGlViewBase<ModelType>::computeNormals()
{
  ENFORCE( !m_vertexBuffer.empty(), "setModelVertices should be called first!" );
  ENFORCE( m_vertexBuffer.size() % 3 == 0, "Vertices must be 3-element vectors" );
  ENFORCE( m_vertexBuffer.size() % 9 == 0, "Triangles must consist of vertices" );

  std::vector< GLfloat > vertexNormals; // will be sent to 'inNormal'

  // for each triangle ( 1 triangle == 3 vertices, 1 vertex == 3 float )
  for ( auto it = m_vertexBuffer.begin(); m_vertexBuffer.end() != it; it += 9 )
  {
    Plane plane( createVec3( it ),
                 createVec3( it + 3 ),
                 createVec3( it + 6 ) );
    auto normal = plane.getNormal();
    // Need to be added 3 times, for each vertex. Inefficient use of GPU memory,
    // but shader implementation is more simple, and ready for Gouraud shading.
    addNormal( vertexNormals, normal );
    addNormal( vertexNormals, normal );
    addNormal( vertexNormals, normal );
  }
  storeDataInGPU( m_normalBufferId, vertexNormals );
  glEnableVertexAttribArray( m_attribLocation_normal );
  glVertexAttribPointer( m_attribLocation_normal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

template<typename ModelType>
void OpenGlViewBase<ModelType>::sendColor( float r, float g, float b )
{
  glUseProgram( m_programId );
  glUniform4f(m_colorUniformId, r, g, b, 0.0f); // TODO use ShaderResourceLocator
}

template<typename ModelType>
auto OpenGlViewBase<ModelType>::getNumberOfVertices() -> std::vector<GLfloat>::size_type
{
  // each vertex has 3 element: x,y,z
  return m_vertexBuffer.size() / 3;
}

  }
}
